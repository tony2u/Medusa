// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;

class CubicEaseInAction :public BaseTweenAction
{
public:
	CubicEaseInAction(BaseFiniteAction* innerAction) :BaseTweenAction(innerAction) {}
	virtual ~CubicEaseInAction(void) {}
public:
	virtual CubicEaseInAction* Clone()const override
	{
		return new CubicEaseInAction(this->mInnerAction);
	}
	virtual CubicEaseInAction* Reverse()const override
	{
		return new CubicEaseInAction((BaseFiniteAction*)this->mInnerAction->Reverse());
	}

	static CubicEaseInAction* Create(CubicEaseInAction* innerAction)
	{
		return new CubicEaseInAction(innerAction);
	}
protected:
	virtual float TransformUpdatePercent(float percent)const override
	{
		return Math::Tween::CubicEaseIn(percent);
	}
};
MEDUSA_END;
