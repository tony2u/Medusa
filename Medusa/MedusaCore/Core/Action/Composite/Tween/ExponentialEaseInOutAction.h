// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class ExponentialEaseInOutAction :public BaseTweenAction
{
public:
	ExponentialEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~ExponentialEaseInOutAction(void) {}
public:
	virtual ExponentialEaseInOutAction* Clone()const override
	{
		return new ExponentialEaseInOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual ExponentialEaseInOutAction* Reverse()const override
	{
		return new ExponentialEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static ExponentialEaseInOutAction* Create(ExponentialEaseInOutAction* innerAction)
	{
		return new ExponentialEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::ExponentialEaseInOut(percent);
	}
};
MEDUSA_END;
