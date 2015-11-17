// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ActionFactory.h"
#include "Core/Action/Composite/SequenceAction.h"
#include "Core/Action/Composite/SpeedAction.h"
#include "Core/Action/Composite/CountDownAction.h"
#include "Core/Action/DelayAction.h"

MEDUSA_BEGIN;



IAction* ActionFactory::Wrap(BaseFiniteAction* action, float speedDuration /*= 0.f*/, float countDownDuration /*= 0.f*/, float delay /*= 0.f*/)
{
	IAction* result = action;

	if (!Math::IsZero(speedDuration))
	{
		result = new SpeedAction(action, action->Duration() / speedDuration);
	}

	if (!Math::IsZero(countDownDuration))
	{
		result = new CountDownAction(result, countDownDuration);
	}

	if (!Math::IsZero(delay))
	{
		DelayAction* delayAction = new DelayAction(delay);
		result = new SequenceAction(delayAction, result);
	}

	return result;
}

MEDUSA_END;
