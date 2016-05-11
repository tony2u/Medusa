// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "LuaStack.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

LuaStack::LuaStack(lua_State* state)
	:mState(state)
{

}

LuaStack::~LuaStack(void)
{

}


void LuaStack::DumpCallStack() const
{
	Log::Info("Lua Call Stack:");

	int level = 0;
	lua_Debug deb;
	while (lua_getstack(mState, level, &deb) == 1)
	{
		lua_getinfo(mState, "nSlu", &deb);
		if (deb.name)
		{
			Log::FormatInfo("{}() : Line {} [{} : line {}]", deb.name, deb.currentline, deb.source, deb.linedefined);
		}
		else
		{
			Log::FormatInfo("unknown : Line {} [{} : line {}]", deb.currentline, deb.source, deb.linedefined);
		}
		++level;
	}
}


void LuaStack::DumpCallStack(lua_State* val)
{
	LuaStack s(val);
	s.DumpCallStack();
}

void LuaStack::Dump() const
{
	RETURN_IF_NULL(mState);

	Log::Info("Lua Stack:");
	int count = lua_gettop(mState);
	for (int i = 1; i <= count; ++i)
	{
		int type = lua_type(mState, i);
		switch (type)
		{
		case LUA_TNIL:
			Log::FormatInfo("{} nil", i);
			break;
		case LUA_TBOOLEAN:
			Log::FormatInfo("{} {}", i, lua_toboolean(mState, i) != 0 ? "True" : "False");
			break;
		case LUA_TLIGHTUSERDATA:
			Log::FormatInfo("{} {}\t0x{:X}", i, lua_typename(mState, type), lua_topointer(mState, i));
			break;
		case LUA_TNUMBER:
			Log::FormatInfo("{} {}\t{}", i, lua_typename(mState, type), lua_tonumber(mState, i));
			break;
		case LUA_TSTRING:
			Log::FormatInfo("{} {}\t{}", i, lua_typename(mState, type), lua_tostring(mState, i));
			break;
		case LUA_TTABLE:
			Log::FormatInfo("{} {}\t0x{:X}", i, lua_typename(mState, type), lua_topointer(mState, i));
			break;
		case LUA_TFUNCTION:
			Log::FormatInfo("{} {}()\t0x{:X}", i, lua_typename(mState, type), lua_topointer(mState, i));
			break;
		case LUA_TUSERDATA:
			Log::FormatInfo("{} {}\t0x{:X}", i, lua_typename(mState, type), lua_topointer(mState, i));
			break;
		case LUA_TTHREAD:
			Log::FormatInfo("{} {}\t0x{:X}", i, lua_typename(mState, type), lua_topointer(mState, i));
			break;
		default:
			Log::FormatInfo("{} {}", i, lua_typename(mState, type));
			break;
		}
	}
}

void LuaStack::Dump(lua_State* val)
{
	LuaStack s(val);
	s.Dump();
}



int LuaStack::RawLength() const
{
	return int(lua_rawlen(mState, -1));
}

int LuaStack::Length() const
{
	return int(luaL_len(mState, -1));
}


int LuaStack::FieldCount(int index /*= -2*/) const
{
	int count = 0;
	lua_pushnil(mState);//first key
	while (lua_next(mState, index) != 0) 
	{
		++count;
		//key at -2,
		//value at -1
		lua_pop(mState, 1);//pop value and use key for next iteration
	}
	return count;
}

bool LuaStack::NewTable(int arraySize /*= 0*/, int recordCount /*= 0*/)
{
	lua_createtable(mState, arraySize, recordCount);
	return IsValid();
}


bool LuaStack::NewTable(StringRef name, int arraySize /*= 0*/, int recordCount /*= 0*/)
{
	Push(name);
	lua_createtable(mState, arraySize, recordCount);
	lua_rawset(mState, -3);
	return true;
}

bool LuaStack::PushMetaTable(int index /*= -1*/) const
{
	lua_getmetatable(mState, index);
	return IsValid();
}

void LuaStack::SetMetaTable(int index /*= -1*/)
{
	lua_setmetatable(mState, index);
}


int LuaStack::SetErrorHandler()const
{
	lua_pushcfunction(mState, OnError);
	return lua_gettop(mState);
}


int LuaStack::OnError(lua_State* state)
{
	if (!lua_isstring(state, 1))
		return 1;
	const char* p=luaL_checkstring(state, 1);
	Log::Error(p);

	lua_getglobal(state, "debug");

	if (!lua_istable(state, -1))
	{
		lua_pop(state, 1);
		return 1;
	}

	lua_getfield(state, -1, "traceback");
	if (!lua_isfunction(state, -1))
	{
		lua_pop(state, 2);
		return 1;
	}

	lua_pushvalue(state, 1);    // pass error message
	lua_call(state, 1, 1);      // call debug.traceback
	return 1;
}
MEDUSA_END;
#endif