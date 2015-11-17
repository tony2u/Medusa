// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StackString.h"

MEDUSA_BEGIN;

class Guid
{
public:
	typedef StackString<64> StringType;

	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];

	static Guid NewGuid();
public:
	StringType ToString()const;
};
MEDUSA_END;