// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class ElasticEaseInAction :public BaseTweenAction
{
public:
	ElasticEaseInAction(BaseFiniteAction* innerAction, float period) :BaseTweenAction(innerAction), mPeriod(period) {}
	virtual ~ElasticEaseInAction(void) {}
public:
	virtual ElasticEaseInAction* Clone()const override
	{
		return new ElasticEaseInAction(this->mInnerAction, mPeriod);
	}
	virtual ElasticEaseInAction* Reverse()const override
	{
		return new ElasticEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse(), mPeriod);
	}

	static ElasticEaseInAction* Create(ElasticEaseInAction* innerAction, float period)
	{
		return new ElasticEaseInAction(innerAction, period);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::ElasticEaseIn(percent, mPeriod);
	}
private:
	float mPeriod;
};
MEDUSA_END;
