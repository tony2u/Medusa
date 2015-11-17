// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class CircularEaseOutAction :public BaseTweenAction
{
public:
	CircularEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~CircularEaseOutAction(void) {}
public:
	virtual CircularEaseOutAction* Clone()const override
	{
		return new CircularEaseOutAction(this->mInnerAction);
	}
	virtual CircularEaseOutAction* Reverse()const override
	{
		return new CircularEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static CircularEaseOutAction* Create(CircularEaseOutAction* innerAction)
	{
		return new CircularEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::CircularEaseOut(percent);
	}
};
MEDUSA_END;
