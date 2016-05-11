// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "TLuaTable.h"

MEDUSA_BEGIN;

class LuaTable:public TLuaTable<LuaTable>
{
public:
	using TLuaTable<LuaTable>::TLuaTable;

};

MEDUSA_END;
#endif