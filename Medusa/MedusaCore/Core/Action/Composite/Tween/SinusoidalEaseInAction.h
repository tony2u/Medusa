// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
class SinusoidalEaseInAction :public BaseTweenAction
{
public:
	SinusoidalEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~SinusoidalEaseInAction(void) {}
public:
	virtual SinusoidalEaseInAction* Clone()const override
	{
		return new SinusoidalEaseInAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual SinusoidalEaseInAction* Reverse()const override
	{
		return new SinusoidalEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static SinusoidalEaseInAction* Create(SinusoidalEaseInAction* innerAction)
	{
		return new SinusoidalEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::SinusoidalEaseIn(percent);
	}
};
MEDUSA_END;
