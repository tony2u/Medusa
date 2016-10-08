// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class BounceEaseInAction :public BaseTweenAction
{
public:
	BounceEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~BounceEaseInAction(void) {}
public:
	virtual BounceEaseInAction* Clone()const override
	{
		return new BounceEaseInAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual BounceEaseInAction* Reverse()const override
	{
		return new BounceEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static BounceEaseInAction* Create(BounceEaseInAction* innerAction)
	{
		return new BounceEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::BounceEaseIn(percent);
	}
};
MEDUSA_END;
