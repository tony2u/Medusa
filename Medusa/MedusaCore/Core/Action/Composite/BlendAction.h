// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseDoubleCompositeFiniteAction.h"

MEDUSA_BEGIN;

class BlendAction :public BaseDoubleCompositeFiniteAction
{
public:
	BlendAction(BaseFiniteAction* from, BaseFiniteAction* to, float blendDuration) :BaseDoubleCompositeFiniteAction(from, to, blendDuration)
	{
		this->mDuration = Math::Min(this->mDuration, from->LeftDuration());
		this->mDuration = Math::Min(this->mDuration, to->Duration());
	}
	virtual ~BlendAction(void) {}

	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		float percent = this->Percent();
		this->mFrom->Update(dt, percent);
		this->mTo->Update(dt, percent);

		return true;
	}

	virtual BlendAction* Reverse()const override { return new BlendAction(this->mTo, this->mFrom, this->mDuration); }
};
MEDUSA_END;
