// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
class SinusoidalEaseOutAction :public BaseTweenAction
{
public:
	SinusoidalEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~SinusoidalEaseOutAction(void) {}
public:
	virtual SinusoidalEaseOutAction* Clone()const override
	{
		return new SinusoidalEaseOutAction(this->mInnerAction);
	}
	virtual SinusoidalEaseOutAction* Reverse()const override
	{
		return new SinusoidalEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static SinusoidalEaseOutAction* Create(SinusoidalEaseOutAction* innerAction)
	{
		return new SinusoidalEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::SinusoidalEaseOut(percent);
	}
};
MEDUSA_END;
