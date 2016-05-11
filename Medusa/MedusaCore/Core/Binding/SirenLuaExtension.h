// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "Core/Lua/LuaCompat.h"

MEDUSA_BEGIN;


class SirenLuaExtension
{
public:
	SirenLuaExtension();
	~SirenLuaExtension(void);

	static int Open(lua_State *L);

};

MEDUSA_END;
#endif
