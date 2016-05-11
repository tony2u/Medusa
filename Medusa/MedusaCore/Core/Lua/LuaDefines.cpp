// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA

#include "LuaDefines.h"

MEDUSA_BEGIN;


namespace LuaNames
{
	const StringRef Name = "___name";
	const StringRef Type = "___type";
	const StringRef Getters = "___getters";
	const StringRef Setters = "___setters";
	const StringRef ClassesTable = "medusa_classes";
	const StringRef Base = "___base";
	const StringRef New = "new";
	const StringRef Delete = "delete";
	const StringRef Node = "___node";





}

namespace LuaMetaMethods
{
	const StringRef Index = "__index";
	const StringRef NewIndex = "__newindex";
	const StringRef Call = "__call";
	const StringRef GC = "__gc";
	const StringRef ToString = "__tostring";
	const StringRef ToWatch = "__towatch";




}

MEDUSA_END;
#endif