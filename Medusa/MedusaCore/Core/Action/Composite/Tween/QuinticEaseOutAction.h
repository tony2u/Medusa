// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuinticEaseOutAction :public BaseTweenAction
{
public:
	QuinticEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuinticEaseOutAction(void) {}
public:
	virtual QuinticEaseOutAction* Clone()const override
	{
		return new QuinticEaseOutAction(this->mInnerAction);
	}
	virtual QuinticEaseOutAction* Reverse()const override
	{
		return new QuinticEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuinticEaseOutAction* Create(QuinticEaseOutAction* innerAction)
	{
		return new QuinticEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuinticEaseOut(percent);
	}
};
MEDUSA_END;
