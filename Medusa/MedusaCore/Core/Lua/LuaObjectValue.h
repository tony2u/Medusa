// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "ILuaObject.h"

MEDUSA_BEGIN;


template<typename T>
class LuaObjectValue :public ILuaObject
{
public:
	LuaObjectValue(lua_State* state) :ILuaObject(state)
	{
	
	}
	virtual ~LuaObjectValue(void)
	{
		if (mState!=nullptr)
		{
			T* obj = static_cast<T*>((void*)&mValue);
			obj->~T();
			mState = nullptr;
		}
	}
public:
	virtual void* ObjectPtr()
	{
		return &mValue;
	}

public:
	template <typename... TArgs>
	static void New(lua_State* state, TArgs&&... args)
	{
		void* buf = Alloc<LuaObjectValue<T>,T>(state);
		LuaObjectValue<T>* obj = ::new(buf) LuaObjectValue<T>(state);
		::new(&obj->mValue) T(std::forward<TArgs>(args)...);
	}

	template <typename... TArgs>
	static void New(lua_State* state, std::tuple<TArgs...>& args)
	{
		void* buf = Alloc<LuaObjectValue<T>, T>(state);
		LuaObjectValue<T>* obj = ::new(buf) LuaObjectValue<T>(state);
		CallConstruct(&obj->mValue, args, typename Compile::MakeIndexes<sizeof...(TArgs)>::type());
	}

	static void New(lua_State* state, const T& other)
	{
		void* buf = Alloc<LuaObjectValue<T>, T>(state);
		LuaObjectValue<T>* obj = ::new(buf) LuaObjectValue<T>(state);
		::new(&obj->mValue) T(other);
	}

protected:
	template <typename... TArgs, size_t... N>
	static T* CallConstruct(std::tuple<TArgs...>& args, const Compile::IndexTuple< N... >&)
	{
		return new T(std::get<N>(args).Value()...);
	}

	template <typename... TArgs, size_t... N>
	static T* CallConstruct(void* mem, std::tuple<TArgs...>& args, const Compile::IndexTuple< N... >&)
	{
		return new(mem) T(std::get<N>(args).Value()...);
	}

	

protected:
	typename std::aligned_storage<sizeof(T), alignof(T)>::type mValue;
	//T mValue;	//cannot use this, because we don't want to call construct twice
	//T* mValue; //also cannot use this, because we want object value to be on lua heap instead of c++ heap
};

MEDUSA_END;
#endif