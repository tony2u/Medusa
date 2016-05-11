// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "LuaStackAutoReset.h"
#include "Core/Log/Log.h"
#include "LuaStack.h"

MEDUSA_BEGIN;

LuaStackAutoReset::LuaStackAutoReset(lua_State* state)
	:mState(state)
{
	LuaStack s(mState);
	mSavedIndex = s.Count();
}

LuaStackAutoReset::LuaStackAutoReset(const LuaStack& stack)
	: mState(stack.State())
{
	mSavedIndex = stack.Count();

}

LuaStackAutoReset::~LuaStackAutoReset(void)
{
	LuaStack s(mState);
	s.SetCount(mSavedIndex);
}


MEDUSA_END;
#endif