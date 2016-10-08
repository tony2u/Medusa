// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
class RateEaseOutAction :public BaseTweenAction
{
public:
	RateEaseOutAction(BaseFiniteAction* innerAction, float rate) :BaseTweenAction(innerAction), mRate(rate) {}
	virtual ~RateEaseOutAction(void) {}
public:
	virtual RateEaseOutAction* Clone()const override
	{
		return new RateEaseOutAction((BaseFiniteAction*)this->mInnerAction, mRate);
	}
	virtual RateEaseOutAction* Reverse()const override
	{
		return new RateEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse(), 1.f / mRate);
	}

	static RateEaseOutAction* Create(RateEaseOutAction* innerAction, float rate)
	{
		return new RateEaseOutAction(innerAction, rate);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::RateEaseOut(percent, mRate);
	}
private:
	float mRate;
};
MEDUSA_END;
