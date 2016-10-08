// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class ElasticEaseOutAction :public BaseTweenAction
{
public:
	ElasticEaseOutAction(BaseFiniteAction* innerAction, float period) :BaseTweenAction(innerAction), mPeriod(period) {}
	virtual ~ElasticEaseOutAction(void) {}
public:
	virtual ElasticEaseOutAction* Clone()const override
	{
		return new ElasticEaseOutAction((BaseFiniteAction*)this->mInnerAction, mPeriod);
	}
	virtual ElasticEaseOutAction* Reverse()const override
	{
		return new ElasticEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse(), mPeriod);
	}

	static ElasticEaseOutAction* Create(ElasticEaseOutAction* innerAction, float period)
	{
		return new ElasticEaseOutAction(innerAction, period);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::ElasticEaseOut(percent, mPeriod);
	}
private:
	float mPeriod;
};
MEDUSA_END;
