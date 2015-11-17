// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuarticEaseInAction :public BaseTweenAction
{
public:
	QuarticEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuarticEaseInAction(void) {}
public:
	virtual QuarticEaseInAction* Clone()const override
	{
		return new QuarticEaseInAction(this->mInnerAction);
	}
	virtual QuarticEaseInAction* Reverse()const override
	{
		return new QuarticEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuarticEaseInAction* Create(QuarticEaseInAction* innerAction)
	{
		return new QuarticEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuarticEaseIn(percent);
	}
};
MEDUSA_END;
