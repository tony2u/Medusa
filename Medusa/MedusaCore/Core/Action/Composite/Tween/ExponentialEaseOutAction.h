// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class ExponentialEaseOutAction :public BaseTweenAction
{
public:
	ExponentialEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~ExponentialEaseOutAction(void) {}
public:
	virtual ExponentialEaseOutAction* Clone()const override
	{
		return new ExponentialEaseOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual ExponentialEaseOutAction* Reverse()const override
	{
		return new ExponentialEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static ExponentialEaseOutAction* Create(ExponentialEaseOutAction* innerAction)
	{
		return new ExponentialEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::ExponentialEaseOut(percent);
	}
};
MEDUSA_END;
