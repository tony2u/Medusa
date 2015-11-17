// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BehaviorFactory.h"
#include "SwitchBehavior.h"
#include "IfBehavior.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


BehaviorFactory::BehaviorFactory()
{
	Register<SwitchBehavior>("SwitchBehavior");
	Register<IfBehavior>("IfBehavior");
}

IBehavior* BehaviorFactory::SmartCreate(StringRef name)
{
	IBehavior* behavior = Create(name);
	if (behavior == nullptr)
	{
		behavior = Create(name + "Behavior");
	}
	Log::AssertNotNullFormat(behavior, "Cannot create behavior with name:{}", name.c_str());
	return behavior;
}


MEDUSA_END;