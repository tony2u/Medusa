// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "ILuaObject.h"
#include "LuaRef.h"

MEDUSA_BEGIN;

ILuaObject::ILuaObject(lua_State* state)
	:mState(state)
{

}

ILuaObject* ILuaObject::GetExactObject(lua_State* state, const std::type_info& typeInfo, int index /*= -1*/)
{

#ifdef MEDUSA_LUA_CHECK_TYPE
	//obj
	LuaStack s(state);

	if (!s.IsUserData(index))
	{
		luaL_error(state, "expect userdata, got %s", lua_typename(state, lua_type(state, index)));
		return nullptr;
	}

	LuaRef classRef = LuaRef::ClassTable(state).Rawget(typeInfo.hash_code());
	if (classRef == nullptr)
	{
		luaL_error(state, "unknown class, you need to register this class with lua-intf first by using LuaBinding");
		return nullptr;
	}

	s.PushMetaTable(index);	//obj,mt
	classRef.PushToStack();	//obj,mt,targetClass

	if (lua_rawequal(state, -1, -2))
	{
		//type is matched
		s.PopNoReturn(2);
	}
	else
	{
		//check inherit from targetClass
		if (CheckInherit(state))
		{
			//type is matched
			s.PopNoReturn(2);
		}
		else
		{
			luaL_error(state, "Type mismatch,override the right metatable? Expect %s, got %s", classRef.Rawget<const char*>(LuaNames::Name), lua_typename(state, lua_type(state, -2)));
			return nullptr;
		}
	}
#endif

	return static_cast<ILuaObject*>(lua_touserdata(state, index));
}

ILuaObject* ILuaObject::GetExactObject(lua_State* state, const StringRef& typeName, int index /*= -1*/)
{
#ifdef MEDUSA_LUA_CHECK_TYPE
	//obj
	LuaStack s(state);

	if (!s.IsUserData(index))
	{
		luaL_error(state, "expect userdata, got %s", lua_typename(state, lua_type(state, index)));
		return nullptr;
	}

	LuaRef classRef = LuaRef::ClassTable(state).Rawget(typeName);
	if (classRef == nullptr)
	{
		luaL_error(state, "unknown class, you need to register this class with lua-intf first by using LuaBinding");
		return nullptr;
	}

	s.PushMetaTable(index);	//obj,mt
	classRef.PushToStack();	//obj,mt,targetClass

	if (lua_rawequal(state, -1, -2))
	{
		//type is matched
		s.PopNoReturn(2);
	}
	else
	{
		//check inherit from targetClass
		if (CheckInherit(state))
		{
			//type is matched
			s.PopNoReturn(2);
		}
		else
		{
			luaL_error(state, "Type mismatch,override the right metatable? Expect %s, got %s", classRef.Rawget<const char*>(LuaNames::Name), lua_typename(state, lua_type(state, -2)));
			return nullptr;
		}
	}
#endif

	return static_cast<ILuaObject*>(lua_touserdata(state, index));
}

bool ILuaObject::CheckInherit(lua_State* state)
{
	//mt,targetClass
	LuaStack s(state);
	LuaStackAutoReset autoReset(s);

	while (true)
	{
		s.PushField(LuaNames::Base, -3);	//mt,targetClass,mtbase
		if (s.IsNull())
		{
			return false;
		}

		s.Duplicate(-2);	//mt,targetClass,mtbase,targetClass
		if (lua_rawequal(state, -1, -2))
		{
			return true;
		}
	}
	return false;
}


MEDUSA_END;

#endif