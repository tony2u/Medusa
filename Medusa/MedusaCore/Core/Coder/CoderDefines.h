// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "CoderType.h"
MEDUSA_BEGIN;

//coders order from higher byte to low byte
//support 8*256 coders
using CoderList = uint64;

enum class CoderFlags
{
	None = 0,
	Block = 1,
	Streaming = 2,
	InPlace = 5,	//In place required block

	All = 7,
};

MEDUSA_END;