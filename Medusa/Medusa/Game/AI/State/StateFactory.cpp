// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StateFactory.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


StateFactory::StateFactory()
{
}

IState* StateFactory::SmartCreate(StringRef name)
{
	IState* state = Create(name);
	if (state == nullptr)
	{
		state = Create(name + "State");
	}
	Log::AssertNotNullFormat(state, "Cannot create state with type:{}", name.c_str());
	return state;
}


MEDUSA_END;