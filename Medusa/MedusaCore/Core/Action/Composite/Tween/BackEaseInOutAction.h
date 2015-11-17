// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class BackEaseInOutAction :public BaseTweenAction
{
public:
	BackEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~BackEaseInOutAction(void) {}
public:
	virtual BackEaseInOutAction* Clone()const override
	{
		return new BackEaseInOutAction(this->mInnerAction);
	}
	virtual BackEaseInOutAction* Reverse()const override
	{
		return new BackEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static BackEaseInOutAction* Create(BackEaseInOutAction* innerAction)
	{
		return new BackEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::BackEaseInOut(percent);
	}
};
MEDUSA_END;
