// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuadraticEaseInAction :public BaseTweenAction
{
public:
	QuadraticEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuadraticEaseInAction(void) {}
public:
	virtual QuadraticEaseInAction* Clone()const override
	{
		return new QuadraticEaseInAction(this->mInnerAction);
	}
	virtual QuadraticEaseInAction* Reverse()const override
	{
		return new QuadraticEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuadraticEaseInAction* Create(QuadraticEaseInAction* innerAction)
	{
		return new QuadraticEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuadraticEaseIn(percent);
	}
};
MEDUSA_END;
