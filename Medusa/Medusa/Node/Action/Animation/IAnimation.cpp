// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IAnimation.h"

MEDUSA_BEGIN;

IAnimation::IAnimation(float duration, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	:BaseFiniteRepeatableCountDownDelayAction(duration, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}

IAnimation::IAnimation(float duration, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: BaseFiniteRepeatableCountDownDelayAction(duration, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{

}


IAnimation::~IAnimation()
{

}




MEDUSA_END;
