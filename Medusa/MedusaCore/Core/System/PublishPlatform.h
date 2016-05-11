// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

MEDUSA_BEGIN;

enum class PublishPlatform
{
	Win = 1,
	IOS = 2,
	Android = 4,
	WindowsPhone = 8,
	all = 15,
};

MEDUSA_END;