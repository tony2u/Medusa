// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuinticEaseInAction :public BaseTweenAction
{
public:
	QuinticEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuinticEaseInAction(void) {}
public:
	virtual QuinticEaseInAction* Clone()const override
	{
		return new QuinticEaseInAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual QuinticEaseInAction* Reverse()const override
	{
		return new QuinticEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuinticEaseInAction* Create(QuinticEaseInAction* innerAction)
	{
		return new QuinticEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuinticEaseIn(percent);
	}
};
MEDUSA_END;
