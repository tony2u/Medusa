// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

class ActionFactory
{
	static IAction* Wrap(BaseFiniteAction* action, float speedDuration = 0.f, float countDownDuration = 0.f, float delay = 0.f);



};

MEDUSA_END;
