// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class RateEaseInAction :public BaseTweenAction
{
public:
	RateEaseInAction(BaseFiniteAction* innerAction, float rate) :BaseTweenAction(innerAction), mRate(rate) {}
	virtual ~RateEaseInAction(void) {}
public:
	virtual RateEaseInAction* Clone()const override
	{
		return new RateEaseInAction((BaseFiniteAction*)this->mInnerAction, mRate);
	}
	virtual RateEaseInAction* Reverse()const override
	{
		return new RateEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse(), 1.f / mRate);
	}

	static RateEaseInAction* Create(RateEaseInAction* innerAction, float rate)
	{
		return new RateEaseInAction(innerAction, rate);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::RateEaseIn(percent, mRate);
	}
private:
	float mRate;
};
MEDUSA_END;
