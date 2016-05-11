// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

namespace LuaNames
{
	const extern StringRef Name;
	const extern StringRef Type;
	const extern StringRef Getters;
	const extern StringRef Setters;
	const extern StringRef ClassesTable;
	const extern StringRef Base;
	const extern StringRef New;
	const extern StringRef Delete;
	const extern StringRef Node;




}

namespace LuaMetaMethods
{
	const extern StringRef Index;
	const extern StringRef NewIndex;
	const extern StringRef Call;
	const extern StringRef GC;
	const extern StringRef ToString;
	const extern StringRef ToWatch;




}



MEDUSA_END;
#endif