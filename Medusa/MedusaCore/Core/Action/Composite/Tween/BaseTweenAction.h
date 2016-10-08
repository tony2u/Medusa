// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseSingleCompositeFiniteAction.h"

MEDUSA_BEGIN;

class BaseTweenAction :public BaseSingleCompositeFiniteAction
{
public:
	BaseTweenAction(BaseFiniteAction* innerAction)
		:BaseSingleCompositeFiniteAction(innerAction,innerAction->Duration())
	{
	}
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(IAction::Update(dt, blend));
		float curPercent = this->Percent();
		this->mElapsed += dt;
		float nowPercent = this->Percent();
		curPercent = TransformUpdatePercent(curPercent);
		nowPercent = TransformUpdatePercent(nowPercent);
		float newDT = (nowPercent - curPercent)*this->mDuration;

		mInnerAction->Update(newDT, blend);

		if (this->mElapsed > this->mDuration)
		{
			mInnerAction->Stop();
			return false;
		}
		return true;
	}
protected:
	virtual float TransformUpdatePercent(float percent)const { return percent; }
};
MEDUSA_END;
