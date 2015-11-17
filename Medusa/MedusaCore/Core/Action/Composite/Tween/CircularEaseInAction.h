// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class CircularEaseInAction :public BaseTweenAction
{
public:
	CircularEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~CircularEaseInAction(void) {}
public:
	virtual CircularEaseInAction* Clone()const override
	{
		return new CircularEaseInAction(this->mInnerAction);
	}
	virtual CircularEaseInAction* Reverse()const override
	{
		return new CircularEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static CircularEaseInAction* Create(CircularEaseInAction* innerAction)
	{
		return new CircularEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::CircularEaseIn(percent);
	}
};
MEDUSA_END;
