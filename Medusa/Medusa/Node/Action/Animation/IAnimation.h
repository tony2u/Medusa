// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteRepeatableCountDownDelayAction.h"

MEDUSA_BEGIN;

class IAnimation :public BaseFiniteRepeatableCountDownDelayAction
{
public:
	IAnimation(float duration, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);
	IAnimation(float duration, bool isRepeatForever, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);

	virtual ~IAnimation();
protected:

};
MEDUSA_END;
