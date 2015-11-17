// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class BackEaseInAction :public BaseTweenAction
{
public:
	BackEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~BackEaseInAction(void) {}
public:
	virtual BackEaseInAction* Clone()const override
	{
		return new BackEaseInAction(this->mInnerAction);
	}
	virtual BackEaseInAction* Reverse()const override
	{
		return new BackEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static BackEaseInAction* Create(BackEaseInAction* innerAction)
	{
		return new BackEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::BackEaseIn(percent);
	}
};
MEDUSA_END;
