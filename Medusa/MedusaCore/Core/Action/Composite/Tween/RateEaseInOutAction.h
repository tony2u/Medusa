// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class RateEaseInOutAction :public BaseTweenAction
{
public:
	RateEaseInOutAction(BaseFiniteAction* innerAction, float rate) :BaseTweenAction(innerAction), mRate(rate) {}
	virtual ~RateEaseInOutAction(void) {}
public:
	virtual RateEaseInOutAction* Clone()const override
	{
		return new RateEaseInOutAction(this->mInnerAction, mRate);
	}
	virtual RateEaseInOutAction* Reverse()const override
	{
		return new RateEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse(), 1.f / mRate);
	}

	static RateEaseInOutAction* Create(RateEaseInOutAction* innerAction, float rate)
	{
		return new RateEaseInOutAction(innerAction, rate);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::RateEaseInOut(percent, mRate);
	}
private:
	float mRate;
};
MEDUSA_END;
