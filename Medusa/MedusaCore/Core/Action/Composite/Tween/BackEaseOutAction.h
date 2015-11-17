// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class BackEaseOutAction :public BaseTweenAction
{
public:
	BackEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~BackEaseOutAction(void) {}
public:
	virtual BackEaseOutAction* Clone()const override
	{
		return new BackEaseOutAction(this->mInnerAction);
	}
	virtual BackEaseOutAction* Reverse()const override
	{
		return new BackEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static BackEaseOutAction* Create(BackEaseOutAction* innerAction)
	{
		return new BackEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::BackEaseOut(percent);
	}
};
MEDUSA_END;
