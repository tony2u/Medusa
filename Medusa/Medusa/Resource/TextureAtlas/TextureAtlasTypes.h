// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreCompiled.h"

MEDUSA_BEGIN;

enum class TextureAtlasFileFormat
{
	MedusaText = 0,
	MedusaBinary = 1,

	Spine = 2,
	Tile=3,
	
	Count = 4,

	//alias
	Libdgx = Spine,
};

MEDUSA_END;