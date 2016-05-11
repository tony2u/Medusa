// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreCompiled.h"

MEDUSA_BEGIN;

enum class TextureAtlasType
{
	None=0,
	MedusaCustom = 1,

	Spine = 2,
	Tile = 4,
	Cocos = 5,

	Count = 6,

	//alias
	Libdgx = Spine,
};

MEDUSA_END;