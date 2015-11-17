// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class CubicEaseOutAction :public BaseTweenAction
{
public:
	CubicEaseOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~CubicEaseOutAction(void) {}
public:
	virtual CubicEaseOutAction* Clone()const override
	{
		return new CubicEaseOutAction(this->mInnerAction);
	}
	virtual CubicEaseOutAction* Reverse()const override
	{
		return new CubicEaseOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static CubicEaseOutAction* Create(CubicEaseOutAction* innerAction)
	{
		return new CubicEaseOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::CubicEaseOut(percent);
	}
};
MEDUSA_END;
