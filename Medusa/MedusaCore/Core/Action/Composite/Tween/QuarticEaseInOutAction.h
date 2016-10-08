// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuarticEaseInOutAction :public BaseTweenAction
{
public:
	QuarticEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuarticEaseInOutAction(void) {}
public:
	virtual QuarticEaseInOutAction* Clone()const override
	{
		return new QuarticEaseInOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual QuarticEaseInOutAction* Reverse()const override
	{
		return new QuarticEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuarticEaseInOutAction* Create(QuarticEaseInOutAction* innerAction)
	{
		return new QuarticEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuarticEaseInOut(percent);
	}
};
MEDUSA_END;
