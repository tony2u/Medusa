// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

MEDUSA_BEGIN;

enum class FilePermission
{
	None = 0,
	Write = 128,
	Read = 256,
	All = 384,
};

MEDUSA_END;