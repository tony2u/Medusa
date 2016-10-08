// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class CubicEaseInOutAction :public BaseTweenAction
{
public:
	CubicEaseInOutAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~CubicEaseInOutAction(void) {}
public:
	virtual CubicEaseInOutAction* Clone()const override
	{
		return new CubicEaseInOutAction((BaseFiniteAction*)this->mInnerAction);
	}
	virtual CubicEaseInOutAction* Reverse()const override
	{
		return new CubicEaseInOutAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static CubicEaseInOutAction* Create(CubicEaseInOutAction* innerAction)
	{
		return new CubicEaseInOutAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::CubicEaseInOut(percent);
	}
};
MEDUSA_END;
