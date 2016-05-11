// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "LuaCompat.h"
#include "LuaArg.h"
#include "Core/Compile/TypeTraits.h"
#include "LuaTypeMapping.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

#pragma region Invoke
template <typename FN, typename R, typename... P>	//return R
struct LuaInvokeMethodBase
{
	template<size_t... N>
	static R Call(const FN& func, std::tuple<P...>& args, const Compile::IndexTuple< N... >&)
	{
		return func(std::get<N>(args).Value()...);
	}
};


template <typename FN, typename R, typename... P>	//return R
struct LuaInvokeMethod
{
	static int Push(lua_State* L, const FN& func, std::tuple<P...>& args)
	{
		LuaType<R>::Push(L, LuaInvokeMethodBase<FN, R, P...>::Call(func, args, typename Compile::MakeIndexes<sizeof...(P)>::type()));
		return 1;
	}
};

template <typename FN, typename... P>	//return void
struct LuaInvokeMethod <FN, void, P...>
{
	static int Push(lua_State*, FN& func, std::tuple<P...>& args)
	{
		LuaInvokeMethodBase<FN, void, P...>::Call(func, args, typename Compile::MakeIndexes<sizeof...(P)>::type());
		return 0;
	}
};

template <typename FN, typename... RP, typename... P>	//return std::tuple,used for multiple return values
struct LuaInvokeMethod <FN, std::tuple<RP...>, P...>
{
	static int Push(lua_State* L, const FN& func, std::tuple<P...>& args)
	{
		std::tuple<RP...> ret = LuaInvokeMethodBase<FN, std::tuple<RP...>, P...>::Call(func, args, typename Compile::MakeIndexes<sizeof...(P)>::type());
		return PushTuple<0, RP...>(L, ret);
	}

private:
	template <size_t INDEX, typename RV0, typename... RV>
	static int PushTuple(lua_State* L, const std::tuple<RP...>& ret)
	{
		LuaType<RV0>::Push(L, std::get<INDEX>(ret));
		return 1 + PushTuple<INDEX + 1, RV...>(L, ret);
	}

	template <size_t INDEX>
	static int PushTuple(lua_State*, const std::tuple<RP...>&)
	{
		return 0;
	}
};

#pragma endregion Invoke


#pragma region Method

//BeginArgIndex default is 1, but at __call meta method, object self will be first argument, so we have to get other args from 2
template <typename F, int BeginArgIndex, typename R, typename... P>
struct LuaBindMethodBase
{
	static int Call(lua_State* L)
	{
		try
		{
			//LuaStack::Dump(L);
			assert(lua_isuserdata(L, lua_upvalueindex(1)));
			F fn = reinterpret_cast<F>(lua_touserdata(L, lua_upvalueindex(1)));
			assert(fn);

			LuaArgTuple<P...> args;
			LuaArgTupleInput<P...>::Get(L, BeginArgIndex, args);	//get input args from stack

			int n = LuaInvokeMethod<F, R, typename LuaArg<P>::HolderType...>::Push(L, fn, args);
			return n + LuaArgTupleOutput<P...>::Push(L, args);
		}
		catch (std::exception& e)
		{
			return luaL_error(L, e.what());
		}
	}
};

template <typename F, typename FArgs = F, int BeginArgIndex = 1, typename TEnabled = void>
struct LuaBindMethod;


template <typename R, typename... P, int IARG>
struct LuaBindMethod <R(*)(P...), R(*)(P...), IARG> : LuaBindMethodBase <R(*)(P...), IARG, R, P...> {};	//normal method pointer


template <typename R, typename... A, typename... P, int IARG>
struct LuaBindMethod <R(*)(A...), Lua::Arg(*)(P...), IARG> : LuaBindMethodBase <R(*)(A...), IARG, R, P...>	//normal method with arg modifier
{
	static_assert(sizeof...(A) == sizeof...(P), "the number of arguments and argument-specs do not match");
};

template <typename FN, int IARG>
struct LuaBindMethod <FN, FN, IARG, typename std::enable_if<std::is_class<FN>::value, void>::type>		//functor or lambada
	: LuaBindMethod <typename Compile::FunctionTraits<FN>::type*, typename Compile::FunctionTraits<FN>::type*, IARG> {};

template <typename FN, typename... P, int IARG>
struct LuaBindMethod <FN, Lua::Arg(*)(P...), IARG, typename std::enable_if<std::is_class<FN>::value, void>::type>	//functor or lambada with arg modifier
	: LuaBindMethod <typename Compile::FunctionTraits<FN>::type*, Lua::Arg(*)(P...), IARG> {};

#pragma endregion Method


#pragma region Class Constructor

template<typename T, typename TArgs, int BeginArgIndex = 1>
struct LuaClassConstructor;

template<typename T, typename... P, int BeginArgIndex>
struct LuaClassConstructor<T, Lua::Arg(*)(P...), BeginArgIndex>
{
	static int Call(lua_State* L)
	{
		try
		{
			LuaArgTuple<P...> args;
			LuaArgTupleInput<P...>::Get(L, BeginArgIndex, args);	//get input args from stack
			LuaObjectValue<T>::New(L, args);
			return 1;
		}
		catch (const std::exception& e)
		{
			return luaL_error(L, e.what());
		}
	}
};

#pragma endregion Class Constructor

#pragma region Invoke Member
template <typename TClass, bool TIsProxy, typename FN, typename R, typename... P>
struct LuaInvokeMemberMethodBase;

template <typename TClass, typename FN, typename R, typename... P>
struct LuaInvokeMemberMethodBase<TClass, true, FN, R, P...>
{
	template<size_t... N>
	static R Call(TClass* obj, const FN& func, std::tuple<P...>& args, const Compile::IndexTuple< N... >&)
	{
		return func(obj, std::get<N>(args).Value()...);
	}
};

template <typename TClass, typename FN, typename R, typename... P>
struct LuaInvokeMemberMethodBase<TClass, false, FN, R, P...>
{
	template<size_t... N>
	static R Call(TClass* obj, const FN& func, std::tuple<P...>& args, const Compile::IndexTuple< N... >&)
	{
		return (obj->*func)(std::get<N>(args).Value()...);
	}
};

template <typename TClass, bool TIsProxy, typename FN, typename R, typename... P>	//return R
struct LuaInvokeMemberMethod
{
	static int Push(lua_State* L, TClass* obj, const FN& func, std::tuple<P...>& args)
	{
		LuaType<R>::Push(L, LuaInvokeMemberMethodBase<TClass, TIsProxy, FN, R, P...>::Call(obj, func, args, typename Compile::MakeIndexes<sizeof...(P)>::type()));
		return 1;
	}

};

template <typename TClass, bool TIsProxy, typename FN, typename... P>	//return void
struct LuaInvokeMemberMethod <TClass, TIsProxy, FN, void, P...>
{
	static int Push(lua_State* L, TClass* obj, const FN& func, std::tuple<P...>& args)
	{
		LuaInvokeMemberMethodBase<TClass, TIsProxy, FN, void, P...>::Call(obj, func, args, typename Compile::MakeIndexes<sizeof...(P)>::type());
		return 0;
	}

};

template <typename FN, bool TIsProxy, typename... RP, typename... P>	//return std::tuple,used for multiple return values
struct LuaInvokeMemberMethod <FN, TIsProxy, std::tuple<RP...>, P...>
{
	static int Push(lua_State* L, const FN& func, std::tuple<P...>& args)
	{
		std::tuple<RP...> ret = LuaInvokeMemberMethodBase<TClass, TIsProxy, FN, std::tuple<RP...>, P...>::Call(obj, func, args, typename Compile::MakeIndexes<sizeof...(P)>::type());
		return PushTuple<0, RP...>(L, ret);
	}

private:
	template <size_t INDEX, typename RV0, typename... RV>
	static int PushTuple(lua_State* L, const std::tuple<RP...>& ret)
	{
		LuaType<RV0>::Push(L, std::get<INDEX>(ret));
		return 1 + PushTuple<INDEX + 1, RV...>(L, ret);
	}

	template <size_t INDEX>
	static int PushTuple(lua_State*, const std::tuple<RP...>&)
	{
		return 0;
	}
};

#pragma endregion Invoke Member

#pragma region Member

template <typename TClass, typename F, typename R, typename... P>
struct LuaBindMemberMethodBase
{
	static int Call(lua_State* L)
	{
		try
		{
			//LuaStack::Dump(L);
			assert(lua_isuserdata(L, lua_upvalueindex(1)));
			F fn = *reinterpret_cast<F*>(lua_touserdata(L, lua_upvalueindex(1)));
			assert(fn);

			TClass* obj = ILuaObject::GetReferenceObject<TClass>(L, 1);

			LuaArgTuple<P...> args;
			LuaArgTupleInput<P...>::Get(L, 2, args);	//get input args from stack

			int n = LuaInvokeMemberMethod<TClass, false, F, R, typename LuaArg<P>::HolderType...>::Push(L, obj, fn, args);
			return n + LuaArgTupleOutput<P...>::Push(L, args);
		}
		catch (std::exception& e)
		{
			return luaL_error(L, e.what());
		}
	}
};


template <typename TClass, typename F, typename FArgs = F, typename TEnabled = void>
struct LuaBindMemberMethod;

template <typename TClass, typename TBase, typename R, typename... P>
struct LuaBindMemberMethod <TClass, R(TBase::*)(P...), R(TBase::*)(P...)> : LuaBindMemberMethodBase <TClass, R(TClass::*)(P...), R, P...>	//normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
};

template <typename TClass, typename TBase, typename R, typename... P>
struct LuaBindMemberMethod <TClass, R(TBase::*)(P...)const, R(TBase::*)(P...)const> : LuaBindMemberMethodBase <TClass, R(TClass::*)(P...)const, R, P...>	//const normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
};


//with arg modifier
template <typename TClass, typename TBase, typename R, typename... A, typename... P>
struct LuaBindMemberMethod <TClass, R(TBase::*)(A...), Lua::Arg(*)(P...)> : LuaBindMemberMethodBase <TClass,  R(TClass::*)(A...), R, P...>	//normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
	static_assert(sizeof...(A) == sizeof...(P), "the number of arguments and argument-specs do not match");
};

template <typename TClass, typename TBase, typename R, typename... A, typename... P>
struct LuaBindMemberMethod <TClass, R(TBase::*)(A...)const, Lua::Arg(*)(P...)> : LuaBindMemberMethodBase <TClass,  R(TClass::*)(A...)const, R, P...>	//const normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
	static_assert(sizeof...(A) == sizeof...(P), "the number of arguments and argument-specs do not match");
};

//std::function

template <typename TClass, typename FN>
struct LuaBindMemberMethod <TClass, FN, FN, typename std::enable_if<std::is_class<FN>::value, void>::type>		//functor or lambada
	: LuaBindMemberMethod <TClass, typename Compile::FunctionTraits<FN>::type*, typename Compile::FunctionTraits<FN>::type*> {};

template <typename TClass, typename FN, typename... P>
struct LuaBindMemberMethod <TClass, FN, Lua::Arg(*)(P...), typename std::enable_if<std::is_class<FN>::value, void>::type>	//functor or lambada with arg modifier
	: LuaBindMemberMethod <TClass, typename Compile::FunctionTraits<FN>::type*, Lua::Arg(*)(P...)> {};


#pragma endregion Member


#pragma region StaticToMember

template <typename TClass, typename F, typename R, typename... P>
struct LuaBindStaticToMemberBase
{
	static int Call(lua_State* L)
	{
		try
		{
			//LuaStack::Dump(L);
			assert(lua_isuserdata(L, lua_upvalueindex(1)));
			F fn = reinterpret_cast<F>(lua_touserdata(L, lua_upvalueindex(1)));
			assert(fn);

			TClass* obj = ILuaObject::GetReferenceObject<TClass>(L, 1);

			LuaArgTuple<P...> args;
			LuaArgTupleInput<P...>::Get(L, 2, args);	//get input args from stack

			int n = LuaInvokeMemberMethod<TClass, true, F, R, typename LuaArg<P>::HolderType...>::Push(L, obj, fn, args);
			return n + LuaArgTupleOutput<P...>::Push(L, args);
		}
		catch (std::exception& e)
		{
			return luaL_error(L, e.what());
		}
	}
};


template <typename TClass, typename F, typename FArgs = F, typename TEnabled = void>
struct LuaBindStaticToMember;



template <typename TClass, typename TBase, typename R, typename... P>
struct LuaBindStaticToMember <TClass, R(*)(TBase*, P...), R(*)(TBase*, P...), typename std::enable_if<!std::is_const<TBase>::value>::type> 
	: LuaBindStaticToMemberBase <TClass, R(*)(TClass*, P...), R, P...>	//static function as member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
};


template <typename TClass, typename TBase, typename R, typename... P>
struct LuaBindStaticToMember <TClass, R(*)(const TBase*, P...), R(*)(const TBase*, P...)> 
	: LuaBindStaticToMemberBase <TClass, R(*)(const TClass*, P...), R, P...>	//static function as const member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
};

//with arg modifier

template <typename TClass, typename TBase, typename R, typename... A, typename... P>
struct LuaBindMemberMethod <TClass, R(*)(TBase*, A...), Lua::Arg(*)(TBase*, P...), typename std::enable_if<!std::is_const<TBase>::value>::type>
	: LuaBindStaticToMemberBase <TClass, R(*)(TClass*, A...), R, P...>	//static function as member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
	static_assert(sizeof...(A) == sizeof...(P), "the number of arguments and argument-specs do not match");
};

template <typename TClass, typename TBase, typename R, typename... A, typename... P>
struct LuaBindStaticToMember <TClass, R(*)(const TBase*, A...), Lua::Arg(*)(const TBase*, P...), typename std::enable_if<!std::is_const<TBase>::value>::type> 
	: LuaBindStaticToMemberBase <TClass, R(*)(const TClass*, A...), R, P...>	//static function as member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
	static_assert(sizeof...(A) == sizeof...(P), "the number of arguments and argument-specs do not match");
};

//std::function

template <typename TClass, typename FN>
struct LuaBindStaticToMember <TClass, FN, FN, typename std::enable_if<std::is_class<FN>::value, void>::type>		//functor or lambada
	: LuaBindStaticToMember <TClass, typename Compile::FunctionTraits<FN>::type*, typename Compile::FunctionTraits<FN>::type*> {};

template <typename TClass, typename FN, typename... P>
struct LuaBindStaticToMember <TClass, FN, Lua::Arg(*)(P...), typename std::enable_if<std::is_class<FN>::value, void>::type>	//functor or lambada with arg modifier
	: LuaBindStaticToMember <TClass, typename Compile::FunctionTraits<FN>::type*, Lua::Arg(*)(P...)> {};


#pragma endregion StaticToMember


#pragma region MemberMethodToStatic

template <typename TClass, typename F, typename R, typename... P>
struct LuaBindMemberMethodToStaticBase
{
	static int Call(lua_State* L)
	{
		try
		{
			assert(lua_isuserdata(L, lua_upvalueindex(1)));
			TClass* obj = ILuaObject::GetReferenceObject<TClass>(L, lua_upvalueindex(1));
			assert(obj);

			assert(lua_isuserdata(L, lua_upvalueindex(2)));
			const F& fn = *reinterpret_cast<const F*>(lua_touserdata(L, lua_upvalueindex(2)));
			assert(fn);

			LuaArgTuple<P...> args;
			LuaArgTupleInput<P...>::Get(L, 1, args);	//get input args from stack

			int n = LuaInvokeMemberMethod<TClass, false, F, R, typename LuaArg<P>::HolderType...>::Push(L, obj, fn, args);
			return n + LuaArgTupleOutput<P...>::Push(L, args);
		}
		catch (std::exception& e)
		{
			return luaL_error(L, e.what());
		}
	}
};


template <typename TClass, typename F, typename FArgs = F, typename TEnabled = void>
struct LuaBindMemberMethodToStatic;

template <typename TClass, typename TBase, typename R, typename... P>
struct LuaBindMemberMethodToStatic <TClass, R(TBase::*)(P...), R(TBase::*)(P...)> : LuaBindMemberMethodToStaticBase <TClass,  R(TClass::*)(P...), R, P...>	//normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
};

template <typename TClass, typename TBase, typename R, typename... P>
struct LuaBindMemberMethodToStatic <TClass, R(TBase::*)(P...)const, R(TBase::*)(P...)const> : LuaBindMemberMethodToStaticBase <TClass,  R(TClass::*)(P...)const, R, P...>	//const normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
};


//with arg modifier
template <typename TClass, typename TBase, typename R, typename... A, typename... P>
struct LuaBindMemberMethodToStatic <TClass, R(TBase::*)(A...), Lua::Arg(*)(P...)> : LuaBindMemberMethodToStaticBase <TClass,  R(TClass::*)(A...), R, P...>	//normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
	static_assert(sizeof...(A) == sizeof...(P), "the number of arguments and argument-specs do not match");
};

template <typename TClass, typename TBase, typename R, typename... A, typename... P>
struct LuaBindMemberMethodToStatic <TClass, R(TBase::*)(A...)const, Lua::Arg(*)(P...)> : LuaBindMemberMethodToStaticBase <TClass, R(TClass::*)(A...)const, R, P...>	//const normal member method
{
	static_assert(std::is_base_of<TBase, TClass>::value, "class type and member function does not match");
	static_assert(sizeof...(A) == sizeof...(P), "the number of arguments and argument-specs do not match");
};

//std::function

template <typename TClass, typename FN>
struct LuaBindMemberMethodToStatic <TClass, FN, FN, typename std::enable_if<std::is_class<FN>::value, void>::type>		//functor or lambada
	: LuaBindMemberMethodToStatic <TClass, typename Compile::FunctionTraits<FN>::type*, typename Compile::FunctionTraits<FN>::type*> {};

template <typename TClass, typename FN, typename... P>
struct LuaBindMemberMethodToStatic <TClass, FN, Lua::Arg(*)(P...), typename std::enable_if<std::is_class<FN>::value, void>::type>	//functor or lambada with arg modifier
	: LuaBindMemberMethodToStatic <TClass, typename Compile::FunctionTraits<FN>::type*, Lua::Arg(*)(P...)> {};


#pragma endregion MemberMethodToStatic
MEDUSA_END
#endif