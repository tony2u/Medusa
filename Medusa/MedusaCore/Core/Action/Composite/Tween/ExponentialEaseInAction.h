// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class ExponentialEaseInAction :public BaseTweenAction
{
public:
	ExponentialEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~ExponentialEaseInAction(void) {}
public:
	virtual ExponentialEaseInAction* Clone()const override
	{
		return new ExponentialEaseInAction(this->mInnerAction);
	}
	virtual ExponentialEaseInAction* Reverse()const override
	{
		return new ExponentialEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static ExponentialEaseInAction* Create(ExponentialEaseInAction* innerAction)
	{
		return new ExponentialEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::ExponentialEaseIn(percent);
	}
};
MEDUSA_END;
