// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuinticEaseInOutAction :public BaseTweenAction
{
public:
	QuinticEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuinticEaseInOutAction(void) {}
public:
	virtual QuinticEaseInOutAction* Clone()const override
	{
		return new QuinticEaseInOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual QuinticEaseInOutAction* Reverse()const override
	{
		return new QuinticEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuinticEaseInOutAction* Create(QuinticEaseInOutAction* innerAction)
	{
		return new QuinticEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuinticEaseInOut(percent);
	}
};
MEDUSA_END;
