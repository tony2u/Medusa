// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class CircularEaseInOutAction :public BaseTweenAction
{
public:
	CircularEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~CircularEaseInOutAction(void) {}
public:
	virtual CircularEaseInOutAction* Clone()const override
	{
		return new CircularEaseInOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual CircularEaseInOutAction* Reverse()const override
	{
		return new CircularEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static CircularEaseInOutAction* Create(CircularEaseInOutAction* innerAction)
	{
		return new CircularEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::CircularEaseInOut(percent);
	}
};
MEDUSA_END;
