// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class BezierAction :public BaseTweenAction
{
public:
	BezierAction(BaseFiniteAction* innerAction, float p0, float p1, float p2, float p3) :BaseTweenAction(innerAction), mP0(p0), mP1(p1), mP2(p2), mP3(p3) {}
	virtual ~BezierAction(void) {}
public:
	virtual BezierAction* Clone()const override
	{
		return new BezierAction(this->mInnerAction, mP0, mP1, mP2, mP3);
	}
	virtual BezierAction* Reverse()const override
	{
		return new BezierAction((BaseFiniteAction*)this->mInnerAction->Reverse(), mP3, mP2, mP1, mP0);
	}

	static BezierAction* Create(BezierAction* innerAction, float p0, float p1, float p2, float p3)
	{
		return new BezierAction(innerAction, p0, p1, p2, p3);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::Bezier3(percent, mP0, mP1, mP2, mP3);
	}
private:
	float mP0;
	float mP1;
	float mP2;
	float mP3;
};
MEDUSA_END;
