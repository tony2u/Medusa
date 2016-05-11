// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

namespace Lua
{
	struct Arg {};

	template<typename T>
	struct Opt {};

	template <typename T, std::intmax_t Value, std::intmax_t Den = 1>
	struct Def {};

	template<typename T>
	struct Out {};

	template<typename T>
	struct Ref {};

	template<typename T>
	struct Ref_Opt {};

	template <typename T, std::intmax_t Value, std::intmax_t Den = 1>
	struct Ref_Def {};
}

#define LUA_ARGS_TYPE(...) Lua::Arg(*)(__VA_ARGS__)
#define LUA_ARGS(...) static_cast<LUA_ARGS_TYPE(__VA_ARGS__)>(nullptr)

#define LUA_FUNC(r, m, ...) static_cast<r(__VA_ARGS__)>(&m)
#define LUA_MEM_FUNC(t, r, m, ...) static_cast<r(t::*)(__VA_ARGS__)>(&t::m)

template <typename T>
struct LuaArgHolder
{
	T& Value()
	{
		return holder;
	}

	const T& Value() const
	{
		return holder;
	}

	void Hold(const T& v)
	{
		holder = v;
	}

	T holder;
};

template <typename T>
struct LuaArgHolder <T&>
{
	T& Value() const
	{
		return *holder;
	}

	void Hold(T& v)
	{
		holder = &v;
	}

	T* holder;
};

template <typename T>
struct LuaArgTraits
{
	using Type = T;
	using ValueType = typename std::result_of<decltype(&LuaType<T>::Get)(lua_State*, int)>::type;	//maybe & for class mapping
	using HolderType = LuaArgHolder<ValueType>;

	static constexpr bool IsInput = true;
	static constexpr bool IsOutput = false;
	static constexpr bool IsOptonal = false;
	static constexpr bool HasDefault = false;
};

template <typename T>
struct LuaArgTraits <Lua::Opt<T>> : LuaArgTraits <T>
{
	using Type = T;
	using ValueType = typename std::decay<T>::type;
	using HolderType = LuaArgHolder<ValueType>;

	static constexpr bool IsOptonal = true;
};

template <typename T, std::intmax_t NUM, std::intmax_t DEN>
struct LuaArgTraits <Lua::Def<T, NUM, DEN>> : LuaArgTraits <Lua::Opt<T>>
{
	static constexpr bool HasDefault = true;
	static constexpr T DefaultValue = T(T(NUM) / DEN);
};

template <typename T>
struct LuaArgTraits <Lua::Out<T>> : LuaArgTraits <T>
{
	static_assert(std::is_lvalue_reference<T>::value&& !std::is_const<typename std::remove_reference<T>::type>::value, "argument with out spec must be non-const reference type");

	static constexpr bool IsInput = false;
	static constexpr bool IsOutput = true;
};

template <typename T>
struct LuaArgTraits <Lua::Ref<T>> : LuaArgTraits <T>
{
	static_assert(std::is_lvalue_reference<T>::value&& !std::is_const<typename std::remove_reference<T>::type>::value, "argument with ref spec must be non-const reference type");
	static constexpr bool IsOutput = true;
};

template <typename T>
struct LuaArgTraits <Lua::Ref_Opt<T>> : LuaArgTraits <Lua::Opt<T>>
{
	static_assert(std::is_lvalue_reference<T>::value&& !std::is_const<typename std::remove_reference<T>::type>::value, "argument with ref spec must be non-const reference type");
	static constexpr bool IsOutput = true;
};

template <typename T, std::intmax_t NUM, std::intmax_t DEN>
struct LuaArgTraits <Lua::Ref_Def<T, NUM, DEN>> : LuaArgTraits <Lua::Def<T, NUM, DEN>>
{
	static_assert(std::is_lvalue_reference<T>::value&& !std::is_const<typename std::remove_reference<T>::type>::value, "argument with ref spec must be non-const reference type");
	static constexpr bool IsOutput = true;
};


template <typename T, bool IsInput, bool IsOptional, bool HasDefault>
struct LuaArgInput;

template <typename Traits, bool IsOptional, bool HasDefault>
struct LuaArgInput <Traits, false, IsOptional, HasDefault>		//is not input
{
	static int Get(lua_State*, int, typename Traits::HolderType&)
	{
		return 0;
	}
};

template <typename Traits, bool HasDefault>
struct LuaArgInput <Traits, true, false, HasDefault>	//is input,is required
{
	static int Get(lua_State* L, int index, typename Traits::HolderType& r)
	{
		r.Hold(LuaType<typename Traits::Type>::Get(L, index));
		return 1;
	}
};

template <typename Traits>
struct LuaArgInput <Traits, true, true, false>	//input,optional, no custom default
{
	static int Get(lua_State* L, int index, typename Traits::HolderType& r)
	{
		using DefaultType = typename std::decay<typename Traits::ValueType>::type;
		r.Hold(LuaType<typename Traits::Type>::Optional(L, index, DefaultType()));
		return 1;
	}
};

template <typename Traits>
struct LuaArgInput <Traits, true, true, true>	//input,optional, has custom default
{
	static int Get(lua_State* L, int index, typename Traits::HolderType& r)
	{
		r.Hold(LuaType<typename Traits::Type>::Optional(L, index, Traits::defaultValue));
		return 1;
	}
};

template <typename Traits, bool IsOutput>
struct LuaArgOutput;

template <typename Traits>
struct LuaArgOutput <Traits, false>
{
	static int Push(lua_State*, const typename Traits::ValueType&)	//not output
	{
		return 0;
	}
};

template <typename Traits>
struct LuaArgOutput <Traits, true>
{
	static int Push(lua_State* L, const typename Traits::ValueType& v)
	{
		LuaType<typename Traits::Type>::Push(L, v);
		return 1;
	}
};


template <typename T>
struct LuaArg
{
	using Traits = LuaArgTraits<T>;
	using Type = typename Traits::Type;
	using HolderType = typename Traits::HolderType;

	static int Get(lua_State* L, int index, HolderType& r)
	{
		return LuaArgInput<Traits, Traits::IsInput, Traits::IsOptonal, Traits::HasDefault>::Get(L, index, r);
	}

	static int Push(lua_State* L, const HolderType& v)
	{
		return LuaArgOutput<Traits, Traits::IsOutput>::Push(L, v.Value());
	}
};

template <typename... P>
using LuaArgTuple = std::tuple<typename LuaArg<P>::HolderType...>;


template <typename... P>
struct LuaArgTupleInput;

template <>
struct LuaArgTupleInput <>
{
	template <typename... T>
	static void Get(lua_State*, int, std::tuple<T...>&)
	{
		// template terminate function
	}
};

template <typename P0, typename... P>
struct LuaArgTupleInput <P0, P...>
{
	template <typename... T>
	static void Get(lua_State* L, int index, std::tuple<T...>& t)
	{
		index += LuaArg<P0>::Get(L, index, std::get<sizeof...(T)-sizeof...(P)-1>(t));
		LuaArgTupleInput<P...>::Get(L, index, t);
	}
};


template <typename... P>
struct LuaArgTupleOutput;

template <>
struct LuaArgTupleOutput <>
{
	template <typename... T>
	static int Push(lua_State*, const std::tuple<T...>&)
	{
		// template terminate function
		return 0;
	}
};

template <typename P0, typename... P>
struct LuaArgTupleOutput <P0, P...>
{
	template <typename... T>
	static int Push(lua_State* L, const std::tuple<T...>& t)
	{
		int n = LuaArg<P0>::Push(L, std::get<sizeof...(T)-sizeof...(P)-1>(t));
		return n + LuaArgTupleOutput<P...>::Push(L, t);
	}
};

MEDUSA_END;
#endif