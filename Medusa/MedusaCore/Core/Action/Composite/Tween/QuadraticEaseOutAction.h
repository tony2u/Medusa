// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuadraticEaseOutAction :public BaseTweenAction
{
public:
	QuadraticEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuadraticEaseOutAction(void) {}
public:
	virtual QuadraticEaseOutAction* Clone()const override
	{
		return new QuadraticEaseOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual QuadraticEaseOutAction* Reverse()const override
	{
		return new QuadraticEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuadraticEaseOutAction* Create(QuadraticEaseOutAction* innerAction)
	{
		return new QuadraticEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuadraticEaseOut(percent);
	}
};
MEDUSA_END;
