// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"

MEDUSA_BEGIN;


class LuaStackAutoReset
{
public:
	LuaStackAutoReset(lua_State* state);
	LuaStackAutoReset(const LuaStack& stack);

	~LuaStackAutoReset(void);

	LuaStackAutoReset(LuaStackAutoReset const &) = delete;
	LuaStackAutoReset(LuaStackAutoReset&&) = delete;
	LuaStackAutoReset& operator=(LuaStackAutoReset const &) = delete;
	LuaStackAutoReset& operator=(LuaStackAutoReset&&) = delete;

private:
	lua_State* mState;
	int mSavedIndex;
};

MEDUSA_END;
#endif