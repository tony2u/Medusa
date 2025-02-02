#pragma once

// allow the user to define a namespace for these functions
#ifndef __FUTURE_NAMESPACE
#define __FUTURE_NAMESPACE std2
#define __FUTURE_NAMESPACE_NEEDS_UNDEF
#endif

#include <type_traits>
#include <memory>
#include <system_error>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace __FUTURE_NAMESPACE
{
namespace __future_detail
{


template<class T>
class associated_state
{
  public:
    associated_state() = default;

    associated_state(const associated_state&) = delete;

    associated_state(associated_state&& other) = default;

    virtual void wait() const = 0;

    virtual T move_value() const = 0;
};


template<class Function>
class deferred_state : public associated_state<typename std::result_of<Function()>::type>
{
  private:
    using value_type = typename std::result_of<Function()>::type;

    Function f_;

  public:
    template<class F>
    explicit deferred_state(F&& f)
      : f_(std::forward<F>(f))
    {}

    virtual void wait() const {}

    virtual value_type move_value() const
    {
      wait();

      return f_();
    }
};


template<class T>
class asynchronous_state : public associated_state<T>
{
  private:
    mutable std::mutex                                                          mutex_;
    mutable std::condition_variable                                             cv_;
    std::exception_ptr                                                          exception_;
    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type storage_;
    bool                                                                        has_value_;

    T* address_of_value() const
    {
      return const_cast<T*>(reinterpret_cast<const T*>(&storage_));
    }

  public:
    asynchronous_state()
      : associated_state<T>(), has_value_(false)
    {}

    asynchronous_state(const asynchronous_state&) = delete;

    asynchronous_state(asynchronous_state&& other) = default;

    bool ready() const
    {
      return exception_ || has_value_;
    }

    void set_exception(std::exception_ptr p)
    {
      {
        std::lock_guard<std::mutex> lock(mutex_);
        exception_ = p;
      }

      cv_.notify_all();
    }

    template<class U>
    void set_value(U&& arg)
    {
      {
        std::lock_guard<std::mutex> lock(mutex_);
        ::new (address_of_value()) T(std::forward<U>(arg));
        has_value_ = true;
      }

      cv_.notify_all();
    }

    void wait() const
    {
      std::unique_lock<std::mutex> lock(mutex_);
      cv_.wait(lock, [&]{ return ready(); });
    }

    T& get() const
    {
      wait();

      if(exception_)
      {
        std::rethrow_exception(exception_);
      }

      return *address_of_value();
    }

    T move_value() const
    {
      return std::move(get());
    }
};


} // end __future_detail


enum class future_errc
{
  broken_promise = 0,
  future_already_retrieved = 1,
  promise_already_satisfied = 2,
  no_state = 3
};


enum class future_status
{
  ready,
  timeout,
  deferred
};

template<typename T> struct is_error_code_enum:public std::false_type{};
template<> struct is_error_code_enum<future_errc> : public std::true_type {};


namespace __future_detail
{


class future_error_category : public std::error_category
{
  public:
    virtual const char* name() const noexcept
    {
      return "future";
    }

    virtual std::string message(int condition) const
    {
      std::string description;

      switch(future_errc(condition))
      {
        case future_errc::broken_promise:
        {
          description = "broken promise";
          break;
        }

        case future_errc::future_already_retrieved:
        {
          description = "future already retrieved";
          break;
        }

        case future_errc::promise_already_satisfied:
        {
          description = "promise already satisfied";
          break;
        }

        case future_errc::no_state:
        {
          description = "no state";
          break;
        }

        default:
        {
          description = "unknown";
          break;
        }
      }

      return std::string("future error: ") + description;
    }
};


} // end __future_detail


const std::error_category& future_category() noexcept
{
  static __future_detail::future_error_category result;
  return result;
}


std::error_code make_error_code(future_errc e) noexcept
{
  return std::error_code(static_cast<int>(e), future_category());
}


std::error_condition make_error_condition(future_errc e) noexcept
{
  return std::error_condition(static_cast<int>(e), future_category());
}


class future_error : public std::logic_error
{
  public:
    future_error(std::error_code ec) : std::logic_error(ec.message()), code_(ec) {}
    const std::error_code& code() const noexcept { return code_; }
  private:
    std::error_code code_;
};


template<class> class promise;


template<class R>
class future
{
  private:
    template<class T>
    struct convert_future
    {
      mutable future<T> fut_;

      convert_future(future<T>&& f) : fut_(std::move(f)) {}

      convert_future(convert_future&& other) = default;

      R operator()() const
      {
        return fut_.get();
      }
    };

    template<class T>
    using conversion_continuation = __future_detail::deferred_state<convert_future<T>>;

    template<class T>
    static conversion_continuation<T> make_conversion_continuation(future<T>&& f)
    {
      return conversion_continuation<T>(convert_future<T>(std::move(f)));
    }


  public:
    future() noexcept : retrieved_(false) {};

    future(future&&) noexcept = default;

    future(const future&) = delete;

    // XXX this is new
    //     we can maybe accelerate the void case
    template<class T>
    future(future<T>&& other,
           typename std::enable_if<
             std::is_void<R>::value ||
             std::is_constructible<R,T&&>::value
           >::type* = 0)
    {
      if(other.valid())
      {
        state_ = std::make_shared<conversion_continuation<T>>(std::move(other));
      }
    }

    ~future() = default;

    future& operator=(const future&) = delete;

    future& operator=(future&&) noexcept = default;

    bool valid() const noexcept
    {
      return static_cast<bool>(state_);
    }

    void wait() const
    {
      if(!state_)
      {
        throw future_error(future_errc::no_state);
      }

      return state_->wait();
    }

    R get()
    {
      if(retrieved_)
      {
        throw future_error(future_errc::future_already_retrieved);
      }

      wait();

      retrieved_ = true;

      return state_->move_value();
    }

  private:
    std::shared_ptr<__future_detail::associated_state<R>> state_;

    bool retrieved_;

    future(const std::shared_ptr<__future_detail::associated_state<R>>& state)
      : state_(state)
    {}

    friend class promise<R>;

    template<class T>
    friend class future;
}; // end future


template<class R>
class promise
{
  public:
    promise()
      : promise(std::allocator_arg, std::allocator<__future_detail::asynchronous_state<R>>())
    {}

    template<class Allocator>
    promise(std::allocator_arg_t, const Allocator& a)
      : state_(std::allocate_shared<__future_detail::asynchronous_state<R>>(a)),
        future_(state_)
    {}

    promise(promise&& other) noexcept
      : state_(std::move(other.state_))
    {}

    promise(const promise&) = delete;

    ~promise()
    {
      if(state_ && !state_->ready())
      {
        abandon_state();
      }
    }

    promise& operator=(promise&& other) noexcept
    {
      abandon_state();
      promise(std::move(other)).swap(*this);
      return *this;
    }

    promise& operator=(const promise&) = delete;

    void swap(promise& other) noexcept
    {
      std::swap(state_, other.state_);
    }

    future<R> get_future()
    {
      check_state_exists();

      if(!future_.valid())
      {
        throw future_error(future_errc::future_already_retrieved);
      }

      return std::move(future_);
    }

    void set_value(const R& r)
    {
      check_can_be_satisfied();

      state_->set_value(r);
    }

    void set_value(R&& r)
    {
      check_can_be_satisfied();

      state_->set_value(std::move(r));
    }

    void set_exception(std::exception_ptr p)
    {
      check_can_be_satisfied();

      state_->set_exception(p);
    }

  private:
    void check_state_exists()
    {
      if(!state_)
      {
        throw future_error(future_errc::no_state);
      }
    }

    void check_can_be_satisfied()
    {
      check_state_exists();

      if(state_->ready())
      {
        throw future_error(future_errc::promise_already_satisfied);
      }
    }

    void abandon_state()
    {
      set_exception(std::make_exception_ptr(future_error(future_errc::broken_promise)));
    }

    std::shared_ptr<__future_detail::asynchronous_state<R>> state_;
    future<R>                                               future_;
};


template<class> class packaged_task;

template<class R, class... ArgTypes>
class packaged_task<R(ArgTypes...)>
{
  public:
    packaged_task() noexcept {}

    template<class F>
    explicit packaged_task(F&& f)
      : packaged_task(std::allocator_arg, std::allocator<R>(), std::forward<F>(f))
    {}

    template<class F, class Allocator>
    explicit packaged_task(std::allocator_arg_t, const Allocator& a, F&& f)
      : task_{std::forward<F>(f)},
        future_(task_.p_.get_future())
    {
    }
    
    ~packaged_task() = default;

    packaged_task(const packaged_task&) = delete;
    packaged_task& operator=(const packaged_task&) = delete;

    packaged_task(packaged_task&&) = default;
    packaged_task& operator=(packaged_task&&) = default;

    bool valid() const noexcept
    {
      return future_.valid();
    }

    future<R> get_future()
    {
      return std::move(future_);
    }

    void operator()(ArgTypes... args)
    {
      // XXX should call INVOKE
      task_(args...);
    }

    void reset()
    {
      *this = packaged_task(std::move(task_));
    }

  private:
    struct task
    {
      std::function<R(ArgTypes...)> f_;
      std::promise<R> p_;

      template<class... Args>
      void operator()(Args&&... args)
      {
        try
        {
          p_.set_value(f_(std::forward<Args>(args)...));
        }
        catch(...)
        {
          p_.set_exception(std::current_exception());
        }
      }
    };

    task task_;
    future<R> future_;
};


} // end namespace

#ifdef __FUTURE_ANNOTATION_NEEDS_UNDEF
#undef __FUTURE_ANNOTATION
#undef __FUTURE_ANNOTATION_NEEDS_UNDEF
#endif

#ifdef __FUTURE_NAMESPACE_NEEDS_UNDEF
#undef __FUTURE_NAMESPACE
#undef __FUTURE_NAMESPACE_NEEDS_UNDEF
#endif

