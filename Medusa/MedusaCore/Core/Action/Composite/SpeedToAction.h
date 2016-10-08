// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseSingleCompositeInfiniteAction.h"

MEDUSA_BEGIN;
class SpeedToAction :public BaseSingleCompositeInfiniteAction
{
public:
	SpeedToAction(BaseFiniteAction* innerAction, float newDuration) :BaseSingleCompositeInfiniteAction(innerAction), mSpeed(newDuration / innerAction->Duration()) {}
	virtual ~SpeedToAction(void) {}
protected:
	virtual float TransformUpdateDuration(float dt)const { return dt*mSpeed; }
private:
	float mSpeed=1.f;
};
MEDUSA_END;
