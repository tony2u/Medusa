// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class BounceEaseInOutAction :public BaseTweenAction
{
public:
	BounceEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~BounceEaseInOutAction(void) {}
public:
	virtual BounceEaseInOutAction* Clone()const override
	{
		return new BounceEaseInOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual BounceEaseInOutAction* Reverse()const override
	{
		return new BounceEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static BounceEaseInOutAction* Create(BounceEaseInOutAction* innerAction)
	{
		return new BounceEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::BounceEaseInOut(percent);
	}
};
MEDUSA_END;
