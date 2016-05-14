// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "LuaModule.h"
#include "LuaStack.h"
#include "LuaState.h"

MEDUSA_BEGIN;

LuaModule::LuaModule(lua_State* state, const StringRef& name /*= StringRef::Empty*/)
	:BaseType(state, name)
{
}

LuaModule::LuaModule(lua_State* state, const LuaRef& self, const StringRef& name /*= StringRef::Empty*/)
	: BaseType(state, self, name)
{

}

LuaModule::~LuaModule(void)
{

}


LuaModule LuaModule::BeginModule(StringRef name)
{
	if (name.IsEmpty())
	{
		Log::AssertFailed("Cannot have empty name lua module");
	}

	auto ref = mRef.Rawget(name);
	if (ref != nullptr)
	{
		return LuaModule(mState, ref, name);
	}
	else
	{
		LuaModule mod(mState, name);
		mRef.Rawset(name, mod.Ref());
		return mod;
	}
}


LuaTable LuaModule::BeginTable(StringRef name)
{
	if (name.IsEmpty())
	{
		Log::AssertFailed("Cannot have empty name lua table");
	}

	auto ref = mRef.Rawget(name);
	if (ref != nullptr)
	{
		return LuaTable(mState, ref, name);
	}
	else
	{
		LuaTable mod(mState, name);
		mRef.Rawset(name, mod.Ref());
		return mod;
	}
}

MEDUSA_END;

#endif