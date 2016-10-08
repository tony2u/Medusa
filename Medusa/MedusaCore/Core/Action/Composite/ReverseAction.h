// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseSingleCompositeFiniteAction.h"

MEDUSA_BEGIN;
class ReverseAction :public BaseSingleCompositeFiniteAction
{
public:
	ReverseAction(BaseFiniteAction* innerAction) :BaseSingleCompositeFiniteAction(innerAction,innerAction->Duration()) {}
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(IAction::Update(dt));
		float curPercent = this->Percent();
		this->mElapsed += dt;
		float nowPercent = this->Percent();
		float newDT = (nowPercent - curPercent)*this->mDuration;

		if (this->mElapsed > this->mDuration)
		{
			this->Stop();
		}

		return mInnerAction->Update(newDT);
	}

	virtual ReverseAction* Reverse()const override { return new ReverseAction((BaseFiniteAction*)this); }
};
MEDUSA_END;
