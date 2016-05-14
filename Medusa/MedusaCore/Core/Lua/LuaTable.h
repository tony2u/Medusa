// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
#include "Core/String/StringRef.h"
#include "LuaDefines.h"
#include "TLuaTable.h"


MEDUSA_BEGIN;


class LuaTable :public TLuaTable<LuaTable>
{
	using BaseType = TLuaTable<LuaTable>;
public:
	LuaTable(lua_State* state, const StringRef& name = StringRef::Empty);
	LuaTable(lua_State* state, const LuaRef& self, const StringRef& name = StringRef::Empty);

	LuaTable(const LuaTable& other) = default;
	LuaTable& operator=(const LuaTable& other) { return (LuaTable&)BaseType::operator=(other); }
	LuaTable(LuaTable&& other) = default;
	LuaTable& operator=(LuaTable&& other) { return (LuaTable&)BaseType::operator=(other); }

	virtual ~LuaTable(void);
public:
	LuaTable BeginTable(StringRef name);
	
private:

};

MEDUSA_END;
#endif