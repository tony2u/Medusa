// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "LuaTable.h"
#include "LuaStack.h"
#include "LuaState.h"

MEDUSA_BEGIN;

LuaTable::LuaTable(lua_State* state, const StringRef& name /*= StringRef::Empty*/)
	:BaseType(state, name)
{
}

LuaTable::LuaTable(lua_State* state, const LuaRef& self, const StringRef& name /*= StringRef::Empty*/)
	: BaseType(state, self, name)
{

}

LuaTable::~LuaTable(void)
{

}


LuaTable LuaTable::BeginTable(StringRef name)
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