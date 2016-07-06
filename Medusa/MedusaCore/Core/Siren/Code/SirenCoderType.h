// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"


// Magic numbers of predefined protocols
enum class SirenCoderType
{
	// Fast binary protocol
	Fast = 0x464d,

	// Compact binary protocol
	Compact = 0x4243,

	// Simple JSON protocol
	Json = 0x4a53,

	// Simple JSON protocol
	Lua = 0x4a63,

	SqlText= 0x4a73,
	SqlBinary = 0x4a83,


};

