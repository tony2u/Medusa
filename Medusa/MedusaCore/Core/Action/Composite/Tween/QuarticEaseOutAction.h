// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class QuarticEaseOutAction :public BaseTweenAction
{
public:
	QuarticEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~QuarticEaseOutAction(void) {}
public:
	virtual QuarticEaseOutAction* Clone()const override
	{
		return new QuarticEaseOutAction(this->mInnerAction);
	}
	virtual QuarticEaseOutAction* Reverse()const override
	{
		return new QuarticEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static QuarticEaseOutAction* Create(QuarticEaseOutAction* innerAction)
	{
		return new QuarticEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::QuarticEaseOut(percent);
	}
};
MEDUSA_END;
