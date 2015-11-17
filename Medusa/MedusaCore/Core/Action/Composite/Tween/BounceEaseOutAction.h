// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class BounceEaseOutAction :public BaseTweenAction
{
public:
	BounceEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~BounceEaseOutAction(void) {}
public:
	virtual BounceEaseOutAction* Clone()const override
	{
		return new BounceEaseOutAction(this->mInnerAction);
	}
	virtual BounceEaseOutAction* Reverse()const override
	{
		return new BounceEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static BounceEaseOutAction* Create(BounceEaseOutAction* innerAction)
	{
		return new BounceEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::BounceEaseOut(percent);
	}
};
MEDUSA_END;
