// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "Core/Compile/TypeTraits.h"


MEDUSA_BEGIN;


template <typename T>
class Delegate;

template<class R, class ...A>
class Delegate<R(A...)>
{
	using WrapperPtr = R(*)(void *, A&&...);
	using GlobalFunctionPtr = R(*)(A&&...);
	using ObjectFactoryPtr = size_t(*)(void*const, const void*);
	template <class C>
	using MemberPair = ::std::pair<C* const, R(C::* const)(A...)>;

	template <class C>
	using ConstMemberPair = ::std::pair<const C* const, R(C::* const)(A...) const>;
public:
	typedef R type(A...);
	typedef R return_type;
	typedef std::tuple<A...> parameters;
public:
	Delegate(void) = default;
	Delegate(::std::nullptr_t const) noexcept { }
	Delegate(const Delegate& other)
		:mWrapper(other.mWrapper),mObjectFactory(other.mObjectFactory)
	{
		if (mObjectFactory != nullptr)
		{
			//copy functor
			size_t size = mObjectFactory(nullptr, nullptr);
			mObject = malloc(size);
			mObjectFactory(mObject, other.mObject);
		}
	}

	Delegate& operator=(const Delegate& other)
	{
		mWrapper = other.mWrapper;
		if (mObjectFactory != nullptr)
		{
			//destruct self
			mObjectFactory(mObject, nullptr);
			size_t selfSize = mObjectFactory(nullptr, nullptr);
			size_t otherSize = other.mObjectFactory(nullptr, nullptr);
			if (otherSize != selfSize)
			{
				mObject = realloc(mObject, otherSize);
			}
			mObjectFactory = other.mObjectFactory;
			//copy construct
			mObjectFactory(mObject, other.mObject);

		}
		else
		{
			mObjectFactory = other.mObjectFactory;
			if (mObjectFactory!=nullptr)
			{
				size_t size = mObjectFactory(nullptr, nullptr);
				mObject = malloc(size);
				mObjectFactory(mObject, other.mObject);
			}
			else
			{
				mObject = other.mObject;
			}
			
		}
		return *this;
	}

	Delegate(Delegate && other)
		:mWrapper(other.mWrapper)
	{
		mObjectFactory = other.mObjectFactory;
		mObject = other.mObject;
		other.mObject = nullptr;
		other.mWrapper = nullptr;
		other.mObjectFactory = nullptr;
	}

	Delegate& operator=(Delegate&& other)
	{
		mWrapper = other.mWrapper;
		if (mObjectFactory != nullptr)
		{
			mObjectFactory(mObject, nullptr);
			free(mObject);
		}
		mObjectFactory = other.mObjectFactory;
		mObject = other.mObject;

		other.mObject = nullptr;
		other.mWrapper = nullptr;
		other.mObjectFactory = nullptr;
		return *this;
	}



#pragma region Global
	//global function ptr
	Delegate(GlobalFunctionPtr ptr) noexcept
		:mObject((void*)ptr), mWrapper(GlobalFunctionWrapper)
	{

	}

	Delegate& operator=(GlobalFunctionPtr ptr)
	{
		if (mObjectFactory != nullptr)
		{
			mObjectFactory(mObject, nullptr);
			free(mObject);
			mObject = nullptr;
			mObjectFactory = nullptr;
		}
		mObject = ptr;
		mWrapper = GlobalFunctionWrapper;
		return *this;
	}
#pragma endregion Global

#pragma region Member
	//method function ptr
	template <class C>
	Delegate(R(C::*const methodPtr)(A...)const, const C* objectPtr)
		:mObject(new ConstMemberPair<C>(objectPtr, methodPtr)),
		mWrapper(ConstMemberFunctionWrapper<C>),
		mObjectFactory(ObjectFactoryWrapper<ConstMemberPair<C>>)
	{

	}

	template <class C>
	Delegate(R(C::*const methodPtr)(A...), C* objectPtr)
		:mObject(new MemberPair<C>(objectPtr, methodPtr)),
		mWrapper(MemberFunctionWrapper<C>),
		mObjectFactory(ObjectFactoryWrapper<MemberPair<C>>)
	{

	}

	template <class C>
	Delegate(R(C::*const methodPtr)(A...)const, const C& objectPtr)
		:mObject(new ConstMemberPair<C>(&objectPtr, methodPtr)),
		mWrapper(ConstMemberFunctionWrapper<C>),
		mObjectFactory(ObjectFactoryWrapper<ConstMemberPair<C>>)
	{

	}

	template <class C>
	Delegate(R(C::*const methodPtr)(A...), C& objectPtr)
		:mObject(new MemberPair<C>(&objectPtr, methodPtr)),
		mWrapper(MemberFunctionWrapper<C>),
		mObjectFactory(ObjectFactoryWrapper<MemberPair<C>>)
	{

	}


#pragma endregion Member
#pragma region Functor

	//functor
	template <typename T, typename = typename ::std::enable_if<!::std::is_same<Delegate, typename ::std::decay<T>::type>::value>::type>
	Delegate(T&& f)
	{
		using functorType = typename ::std::decay<T>::type;
		mObject = new functorType(::std::forward<T>(f));
		mWrapper = FunctorWrapper<functorType>;
		mObjectFactory = ObjectFactoryWrapper<functorType>;
	}

	template <typename T, typename = typename ::std::enable_if<!::std::is_same<Delegate, typename ::std::decay<T>::type>::value>::type>
	Delegate & operator=(T&& f)
	{
		using functorType = typename ::std::decay<T>::type;
		if (mObjectFactory != nullptr)
		{
			size_t functorSize = mObjectFactory(nullptr, nullptr);
			mObjectFactory(mObject, nullptr);

			if ((sizeof(functorType) > functorSize))
			{
				mObject = realloc(mObject, sizeof(functorType));
			}

			new(mObject) functorType(::std::forward<T>(f));
		}
		else
		{
			mObject = new functorType(::std::forward<T>(f));
		}
		mWrapper = FunctorWrapper<functorType>;
		mObjectFactory = ObjectFactoryWrapper<functorType>;
		return *this;
	}

#pragma endregion Functor

	~Delegate()
	{
		Reset();
	}

	void Reset(void)
	{
		if (mObjectFactory != nullptr)
		{
			mObjectFactory(mObject, nullptr);
			free(mObject);
			mObject = nullptr;
			mObjectFactory = nullptr;
		}
		mWrapper = nullptr;
	}

	void Swap(Delegate & other) noexcept { ::std::swap(*this, other); }

	R operator()(A... args) const
	{
		assert(mWrapper);
		return mWrapper(mObject, ::std::forward<A>(args)...);
	}

	R TryInvoke(A... args) const
	{
		if (*this)
		{
			return mWrapper(mObject, ::std::forward<A>(args)...);
		}
		return Compile::DefaultValue<R>();
	}

	bool operator==(const Delegate& rhs) const noexcept
	{
		// comparison between functor and non-functor is left as undefined at the moment.
		if (mObjectFactory && rhs.mObjectFactory) // both functors
		{
			return mObjectFactory == rhs.mObjectFactory && mWrapper == rhs.mWrapper && (::memcmp(mObject, rhs.mObject, mObjectFactory(nullptr, nullptr)) == 0);
		}
		return (mObject == rhs.mObject) && (mWrapper == rhs.mWrapper);
	}

	int Compare(const Delegate& rhs) const noexcept
	{
		int r = mObjectFactory - rhs.mObjectFactory;
		if (r != 0)
		{
			return r;
		}
		r = mWrapper - rhs.mWrapper;
		if (r != 0)
		{
			return r;
		}
		return ::memcmp(mObject, rhs.mObject, mObjectFactory(nullptr, nullptr));
	}

	bool operator!=(Delegate const & rhs) const noexcept { return !operator==(rhs); }
	bool operator<(Delegate const & rhs) const noexcept { return Compare(rhs) < 0; }
	bool operator<=(Delegate const & rhs) const noexcept { return Compare(rhs) <= 0; }
	bool operator>(Delegate const & rhs) const noexcept { return Compare(rhs) > 0; }
	bool operator>=(Delegate const & rhs) const noexcept { return Compare(rhs) >= 0; }

	bool operator==(::std::nullptr_t const) const noexcept { return mWrapper==nullptr; }
	bool operator!=(::std::nullptr_t const) const noexcept { return mWrapper!=nullptr; }

	friend bool operator==(::std::nullptr_t, const Delegate& other) noexcept { return other.mWrapper==nullptr; }
	friend bool operator!=(::std::nullptr_t, const Delegate& other) noexcept { return other.mWrapper!=nullptr; }

	explicit operator bool() const noexcept { return mWrapper!=nullptr; }
	int HashCode()const
	{
		return mObjectFactory^mWrapper ^ (mObject);
	}
public:
	template <R(*const functionPtr)(A...)>
	static Delegate Bind(void) noexcept
	{
		return{ GlobalFunctionTemplateWrapper<functionPtr>,nullptr };
	}

	template <class C, R(C::* const methodPtr)(A...)>
	static Delegate Bind(C* objectPtr) noexcept
	{
		return{ MemberFunctionTemplateWrapper<C, methodPtr>,objectPtr };
	}

	template <class C, R(C::* const methodPtr)(A...) const>
	static Delegate Bind(const C* objectPtr) noexcept
	{
		return{ ConstMemberFunctionTemplateWrapper<C, methodPtr> ,const_cast<C*>(objectPtr) };
	}

	template <class C, R(C::* const methodPtr)(A...)>
	static Delegate Bind(C& object) noexcept
	{
		return{MemberFunctionTemplateWrapper<C, methodPtr>, &object };
	}

	template <class C, R(C::* const methodPtr)(A...) const>
	static Delegate Bind(const C& object) noexcept
	{
		return{  ConstMemberFunctionTemplateWrapper<C, methodPtr>,const_cast<C*>(&object) };
	}

	template <typename T>
	static Delegate Bind(T && f)
	{
		return ::std::forward<T>(f);
	}

	static Delegate Bind(R(*const functionPtr)(A...))
	{
		return functionPtr;
	}

	template <class C>
	static Delegate Bind(C * const objectPtr, R(C::* const methodPtr)(A...))
	{
		return Delegate(methodPtr, objectPtr);
	}

	template <class C>
	static Delegate Bind(C const * const objectPtr, R(C::* const methodPtr)(A...) const)
	{
		return Delegate(methodPtr, objectPtr);
	}

	template <class C>
	static Delegate Bind(C & object, R(C::* const methodPtr)(A...))
	{
		return Delegate( methodPtr, object);
	}

	template <class C>
	static Delegate Bind(C const & object, R(C::* const methodPtr)(A...) const)
	{
		return Delegate(methodPtr, object);
	}

private:
	Delegate(void*const objectPtr, WrapperPtr const wrapper) noexcept
		: mObject(objectPtr), mWrapper(wrapper)
	{

	}

	template <class T>
	static size_t ObjectFactoryWrapper(void*const objectPtr, const void* val = nullptr)
	{
		if (objectPtr != nullptr)
		{
			if (val != nullptr)
			{
				//construct
				new (objectPtr) T(*(T*)val);
			}
			else
			{
				static_cast<T *>(objectPtr)->~T();
			}
		}
		return sizeof(T);
	}

	static R GlobalFunctionWrapper(void *const objectPtr, A && ... args)
	{
		return ((GlobalFunctionPtr)objectPtr)(::std::forward<A>(args)...);
	}

	template <typename C>
	static R MemberFunctionWrapper(void * const objectPtr, A && ... args)
	{
		using functorType = MemberPair<C>;
		return (static_cast<functorType *>(objectPtr)->first->*static_cast<functorType *>(objectPtr)->second)(::std::forward<A>(args)...);
	}

	template <typename C>
	static R ConstMemberFunctionWrapper(void * const objectPtr, A && ... args)
	{
		using functorType = ConstMemberPair<C>;
		return (static_cast<functorType *>(objectPtr)->first->*static_cast<functorType *>(objectPtr)->second)(::std::forward<A>(args)...);
	}

	template <typename T>
	static R FunctorWrapper(void * const objectPtr, A && ... args)
	{
		return (*static_cast<T *>(objectPtr))(::std::forward<A>(args)...);
	}

	template <R(*functionPtr)(A...)>
	static R GlobalFunctionTemplateWrapper(void * const, A && ... args)
	{
		return functionPtr(::std::forward<A>(args)...);
	}

	template <class C, R(C::*methodPtr)(A...)>
	static R MemberFunctionTemplateWrapper(void * const objectPtr, A && ... args)
	{
		return (static_cast<C *>(objectPtr)->*methodPtr)(::std::forward<A>(args)...);
	}

	template <class C, R(C::*methodPtr)(A...) const>
	static R ConstMemberFunctionTemplateWrapper(void * const objectPtr, A && ... args)
	{
		return (static_cast<C const *>(objectPtr)->*methodPtr)(::std::forward<A>(args)...);
	}
private:
	void * mObject = nullptr;
	WrapperPtr mWrapper = nullptr;
	ObjectFactoryPtr mObjectFactory = nullptr;
};


namespace placeholder
{
	template <int N>
	struct TPlaceHolder {};
#ifdef MEDUSA_WINDOWS
	constexpr TPlaceHolder<1> _1;
	constexpr TPlaceHolder<2> _2;
	constexpr TPlaceHolder<3> _3;
	constexpr TPlaceHolder<4> _4;
	constexpr TPlaceHolder<5> _5;
	constexpr TPlaceHolder<6>  _6;
	constexpr TPlaceHolder<7>  _7;
	constexpr TPlaceHolder<8>  _8;
	constexpr TPlaceHolder<9>  _9;
	constexpr TPlaceHolder<10> _10;
	constexpr TPlaceHolder<11> _11;
	constexpr TPlaceHolder<12> _12;
	constexpr TPlaceHolder<13> _13;
	constexpr TPlaceHolder<14> _14;
	constexpr TPlaceHolder<15> _15;
	constexpr TPlaceHolder<16> _16;
	constexpr TPlaceHolder<17> _17;
	constexpr TPlaceHolder<18> _18;
	constexpr TPlaceHolder<19> _19;
	constexpr TPlaceHolder<20> _20;
#else
	extern const TPlaceHolder<1> _1;
	extern const TPlaceHolder<2> _2;
	extern const TPlaceHolder<3> _3;
	extern const TPlaceHolder<4> _4;
	extern const TPlaceHolder<5> _5;
	extern const TPlaceHolder<6>  _6;
	extern const TPlaceHolder<7>  _7;
	extern const TPlaceHolder<8>  _8;
	extern const TPlaceHolder<9>  _9;
	extern const TPlaceHolder<10> _10;
	extern const TPlaceHolder<11> _11;
	extern const TPlaceHolder<12> _12;
	extern const TPlaceHolder<13> _13;
	extern const TPlaceHolder<14> _14;
	extern const TPlaceHolder<15> _15;
	extern const TPlaceHolder<16> _16;
	extern const TPlaceHolder<17> _17;
	extern const TPlaceHolder<18> _18;
	extern const TPlaceHolder<19> _19;
	extern const TPlaceHolder<20> _20;
#endif
	

	
}

namespace BindDetail
{
	template<typename TFunc, typename... TArgs>
	class Binder	//[IGNORE_PRE_DECLARE]
	{
		using ArgsTuple = std::tuple<typename std::decay<TArgs>::type...>;
		using FunctorType = typename std::decay<TFunc>::type;
		using ResultType = typename Compile::FunctionTraits<FunctorType>::return_type;

		template <typename T, class TupleT>
		inline auto SelectArg(TupleT& /*tp*/, T&& val)const->T&&
		{
			return std::forward<T>(val);
		}

		template <int N, class TupleT>
		inline auto SelectArg(TupleT& tp, placeholder::TPlaceHolder<N>) const-> decltype(std::get<N - 1>(tp))
		{
			return std::get<N - 1>(tp);
		}
	public:
		Binder(Binder&&) = default;
		Binder(const Binder&) = default;

		Binder(TFunc&& f, TArgs&&... args)
			:mFunctor(std::forward<TFunc>(f)),
			mArgs(std::forward<TArgs>(args)...)
		{}

		template <typename... TArgs2>
		inline ResultType operator()(TArgs2&&... args)const
		{
			return DoCall(std::forward_as_tuple(std::forward<TArgs2>(args)...), typename Compile::MakeIndexes<sizeof...(TArgs)>::type());
		}
	private:
		template <class TupleT, int... N>
		inline ResultType DoCall(TupleT&& tp, const Compile::IndexTuple< N... >&)const
		{
			return Invoke<FunctorType>(SelectArg(tp, std::get<N>(mArgs))...);
		}

		//global function and functor
		template < typename F, typename... TArgs2>
		inline typename std::enable_if<!std::is_member_function_pointer<F>::value, ResultType>::type Invoke(TArgs2&&... args)const
		{
			return (mFunctor)(std::forward<TArgs2>(args)...);
		}

		//member function
		template <typename F, typename P1, typename... TArgs2>
		inline typename std::enable_if<std::is_member_function_pointer<F>::value &&std::is_pointer<typename std::decay<P1>::type>::value, ResultType>::type Invoke(P1&& this_ptr, TArgs2&&... args)const
		{
			return (std::forward<P1>(this_ptr)->*mFunctor)(std::forward<TArgs2>(args)...);
		}

		template <typename F, typename P1, typename... TArgs2>
		inline typename std::enable_if<std::is_member_function_pointer<F>::value &&!std::is_pointer<typename std::decay<P1>::type>::value && !Compile::IsReferenceWrapper<P1>::value, ResultType>::type Invoke(P1&& this_obj, TArgs2&&... args)const
		{
			return (std::forward<P1>(this_obj).*mFunctor)(std::forward<TArgs2>(args)...);
		}

		template <typename F, typename P1, typename... TArgs2>
		inline typename std::enable_if<std::is_member_function_pointer<F>::value &&!std::is_pointer<typename std::decay<P1>::type>::value && Compile::IsReferenceWrapper<P1>::value, ResultType>::type Invoke(P1&& this_wrp, TArgs2&&... args)const
		{
			typedef typename std::remove_reference<P1>::type wrapper_t;
			typedef typename wrapper_t::type this_t;
			return (static_cast<this_t&>(std::forward<P1>(this_wrp)).*mFunctor)(std::forward<TArgs2>(args)...);
		}
	private:
		FunctorType mFunctor;
		ArgsTuple     mArgs;
	};

}
//global function
template<class R, class ...A>
static Delegate<R(A...)> Bind(R(*val)(A...)) noexcept
{
	return Delegate<R(A...)>(val);
}

template<class C, class R, class ...A>
static Delegate<R(A...)> Bind(R(C::* const methodPtr)(A...), C * const objectPtr)
{
	return Delegate<R(A...)>(methodPtr, objectPtr);
}

template<class C, class R, class ...A>
static Delegate<R(A...)> Bind(R(C::* const methodPtr)(A...) const, C const * const objectPtr)
{
	return Delegate<R(A...)>(methodPtr, objectPtr);
}

template<class C, class R, class ...A>
static Delegate<R(A...)> Bind(R(C::* const methodPtr)(A...), C & object)
{
	return Delegate<R(A...)>(methodPtr, object);
}

template<class C, class R, class ...A>
static Delegate<R(A...)> Bind(R(C::* const methodPtr)(A...) const, C const & object)
{
	return Delegate<R(A...)>(methodPtr, object);
}


template<typename T, typename Tlimit = typename std::enable_if<!std::is_pointer<T>::value>::type>
static Delegate<typename Compile::FunctionTraits<T>::type> Bind(T&& f) noexcept
{
	return Delegate<typename Compile::FunctionTraits<T>::type >(f);
}


//template <typename TFunc, typename TArg1, typename... TArgs,
//	typename Tlimit= typename std::enable_if<
//	(std::is_member_function_pointer<TFunc>::value&&!std::is_same<typename std::decay<TArg1>::type, typename Compile::FunctionTraits<TFunc>::ClassType>::value) || (!std::is_member_function_pointer<TFunc>::value),
//	void>::type>
//	inline BindDetail::Binder<TFunc&&, TArg1&&, TArgs&&...> Bind(TFunc&& f, TArg1&& arg1, TArgs&&... args)
//{
//	return BindDetail::Binder<TFunc&&, TArg1&&, TArgs&&...>(std::forward<TFunc>(f), std::forward<TArg1>(arg1), std::forward<TArgs>(args)...);
//}


template <typename TFunc, typename TArg1, typename... TArgs,
	typename Tlimit = typename std::enable_if<
	(std::is_member_function_pointer<TFunc>::value&&((!std::is_same<typename std::decay<TArg1>::type, typename Compile::FunctionTraits<TFunc>::ClassType>::value)||sizeof...(TArgs)>0)) //accept >0 args for member function
	|| (!std::is_pointer<TFunc>::value),	//is functor
	void>::type>
	inline BindDetail::Binder<TFunc&&, TArg1&&, TArgs&&...> Bind(TFunc&& f, TArg1&& arg1, TArgs&&... args)
{
	return BindDetail::Binder<TFunc&&, TArg1&&, TArgs&&...>(std::forward<TFunc>(f), std::forward<TArg1>(arg1), std::forward<TArgs>(args)...);
}


//[PRE_DECLARE_BEGIN]
typedef Delegate<void()> Action0;
typedef Delegate<void(void*)> Action1;
//[PRE_DECLARE_END]




MEDUSA_END