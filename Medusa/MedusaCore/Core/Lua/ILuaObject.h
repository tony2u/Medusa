// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "LuaCompat.h"
#include "LuaDefines.h"

MEDUSA_BEGIN;


class ILuaObject
{
public:
	ILuaObject(lua_State* state);
	virtual ~ILuaObject(void){}

	lua_State* State() const { return mState; }
	void SetState(lua_State* val) { mState = val; }

	template<typename T>
	static ILuaObject* GetExactObject(lua_State* state,int index=-1)
	{
		return GetExactObject(state, typeid(T),index);
	}

	template<typename T>
	static T* GetReferenceObject(lua_State* state, int index = -1)
	{
		return static_cast<T*>(GetExactObject(state, typeid(T), index)->ObjectPtr());
	}

	template<typename T>
	static T* GetReferenceObject(lua_State* state, const StringRef& typeName, int index = -1)
	{
		return static_cast<T*>(GetExactObject(state, typeName, index)->ObjectPtr());
	}

	static ILuaObject* GetExactObject(lua_State* state, const std::type_info& typeInfo, int index = -1);
	static ILuaObject* GetExactObject(lua_State* state, const StringRef& typeName, int index = -1);

	static bool CheckInherit(lua_State* state);


public:
	virtual void* ObjectPtr() = 0;

protected:
	template<typename T, typename TClass>
	static void* Alloc(lua_State* state)
	{
		void* buf = lua_newuserdata(state, sizeof(T));

		lua_pushstring(state, LuaNames::ClassesTable.c_str());
		lua_gettable(state, LUA_REGISTRYINDEX);

		lua_pushinteger(state, typeid(TClass).hash_code());
		lua_rawget(state, -2);//meta

		if (lua_isnoneornil(state,-1))
		{
			Log::AssertFailedFormat("Cannot find class:{}", typeid(TClass).name());
			return nullptr;
		}
		lua_setmetatable(state, -3);
		lua_pop(state, 1);
		return buf;
	}

	template<typename T>
	static void* Alloc(lua_State* state,const StringRef& typeName)
	{
		void* buf = lua_newuserdata(state, sizeof(T));

		lua_pushstring(state, LuaNames::ClassesTable.c_str());
		lua_gettable(state, LUA_REGISTRYINDEX);

		lua_pushstring(state, typeName.c_str());
		lua_rawget(state, -2);//meta

		if (lua_isnoneornil(state, -1))
		{
			Log::AssertFailedFormat("Cannot find class:{}", typeName);
			return nullptr;
		}
		lua_setmetatable(state, -3);
		lua_pop(state, 1);
		return buf;
	}


protected:
	lua_State* mState = nullptr;
};

MEDUSA_END;
#endif