// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "ILuaObject.h"

MEDUSA_BEGIN;

template<typename T>
struct LuaCustomObjectPtr 
{
	T* Ptr;
	StringRef TypeName;
};


//The lifetime of the object is managed by C++.
template<typename T>
class LuaObjectPtr :public ILuaObject
{
public:
	LuaObjectPtr(lua_State* state) :ILuaObject(state)
	{
	
	}
	virtual ~LuaObjectPtr(void)
	{
		mPtr = nullptr;
	}
public:
	virtual void* ObjectPtr()
	{
		return mPtr;
	}

public:
	static void New(lua_State* state, const T& other)
	{
		void* buf = Alloc<LuaObjectPtr<T>, T>(state);
		LuaObjectPtr<T>* obj = ::new(buf) LuaObjectPtr<T>(state);
		obj->mPtr = (void*)&other;
	}

	static void New(lua_State* state, const T* other)
	{
		void* buf = Alloc<LuaObjectPtr<T>, T>(state);
		LuaObjectPtr<T>* obj = ::new(buf) LuaObjectPtr<T>(state);
		obj->mPtr = (void*)other;
	}

	static void New(lua_State* state, const T& other,const StringRef& typeName)
	{
		void* buf = Alloc<LuaObjectPtr<T>>(state, typeName);
		LuaObjectPtr<T>* obj = ::new(buf) LuaObjectPtr<T>(state);
		obj->mPtr = (void*)&other;
	}

	static void New(lua_State* state, const T* other, const StringRef& typeName)
	{
		void* buf = Alloc<LuaObjectPtr<T>>(state, typeName);
		LuaObjectPtr<T>* obj = ::new(buf) LuaObjectPtr<T>(state);
		obj->mPtr = (void*)other;
	}
protected:
	void* mPtr;
};

MEDUSA_END;
#endif