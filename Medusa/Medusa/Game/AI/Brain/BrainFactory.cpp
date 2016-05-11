// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BrainFactory.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;



IBrain* BrainFactory::SmartCreate(StringRef name)
{
	IBrain* brain = Create(name);
	if (brain == nullptr)
	{
		brain = Create(name + "Brain");
	}
	Log::AssertNotNullFormat(brain, "Cannot create brain with name:{}", name.c_str());

	return brain;
}

MEDUSA_END;