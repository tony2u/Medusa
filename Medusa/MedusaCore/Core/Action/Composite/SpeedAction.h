// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseSingleCompositeInfiniteAction.h"

MEDUSA_BEGIN;
/*
Changes the speed of an action, making it take longer (speed>1)
or less (speed<1) time.
Useful to simulate 'slow motion' or 'fast forward' effect.
*/

class SpeedAction :public BaseSingleCompositeInfiniteAction
{
public:
	SpeedAction(IAction* innerAction, float speed) :BaseSingleCompositeInfiniteAction(innerAction), mSpeed(speed) {}
	virtual ~SpeedAction(void) {}
	virtual SpeedAction* Reverse()const override{ return new SpeedAction(this->mInnerAction,1.f/mSpeed); }

	virtual RunningState State() const override { return mInnerAction->State(); }
	virtual bool IsRunning()const override { return mInnerAction->IsRunning(); }
	virtual bool IsDone()const override { return mInnerAction->IsDone(); }
protected:
	virtual float TransformUpdateDuration(float dt)const override { return dt*mSpeed; }
private:
	float mSpeed;
};
MEDUSA_END;
