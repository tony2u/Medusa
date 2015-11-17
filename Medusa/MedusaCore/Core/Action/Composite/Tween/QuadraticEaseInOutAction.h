// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuadraticEaseInOutAction :public BaseTweenAction
{
public:
	QuadraticEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuadraticEaseInOutAction(void) {}
public:
	virtual QuadraticEaseInOutAction* Clone()const override
	{
		return new QuadraticEaseInOutAction(this->mInnerAction);
	}
	virtual QuadraticEaseInOutAction* Reverse()const override
	{
		return new QuadraticEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuadraticEaseInOutAction* Create(QuadraticEaseInOutAction* innerAction)
	{
		return new QuadraticEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuadraticEaseInOut(percent);
	}
};
MEDUSA_END;
