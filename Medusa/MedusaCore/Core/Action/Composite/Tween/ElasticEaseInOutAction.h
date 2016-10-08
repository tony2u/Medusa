// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class ElasticEaseInOutAction :public BaseTweenAction
{
public:
	ElasticEaseInOutAction(BaseFiniteAction* innerAction, float period) :BaseTweenAction(innerAction), mPeriod(period) {}
	virtual ~ElasticEaseInOutAction(void) {}
public:
	virtual ElasticEaseInOutAction* Clone()const override
	{
		return new ElasticEaseInOutAction((BaseFiniteAction*)this->mInnerAction, mPeriod);
	}
	virtual ElasticEaseInOutAction* Reverse()const override
	{
		return new ElasticEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse(), mPeriod);
	}

	static ElasticEaseInOutAction* Create(ElasticEaseInOutAction* innerAction, float period)
	{
		return new ElasticEaseInOutAction(innerAction, period);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::ElasticEaseInOut(percent, mPeriod);
	}
private:
	float mPeriod;
};
MEDUSA_END;
