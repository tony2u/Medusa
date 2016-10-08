// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
class SinusoidalEaseInOutAction :public BaseTweenAction
{
public:
	SinusoidalEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~SinusoidalEaseInOutAction(void) {}
public:
	virtual SinusoidalEaseInOutAction* Clone()const override
	{
		return new SinusoidalEaseInOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual SinusoidalEaseInOutAction* Reverse()const override
	{
		return new SinusoidalEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static SinusoidalEaseInOutAction* Create(SinusoidalEaseInOutAction* innerAction)
	{
		return new SinusoidalEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::SinusoidalEaseInOut(percent);
	}
};
MEDUSA_END;
