// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "RepeatedForeverAction.h"

MEDUSA_BEGIN;


RepeatedForeverAction::~RepeatedForeverAction(void)
{

}

bool RepeatedForeverAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt, blend));
	switch (this->mInnerAction->Type())
	{
		case ActionType::Instant:
			this->mInnerAction->Start();
			break;
		case ActionType::Finite:
		{
			BaseFiniteAction& action = (BaseFiniteAction&)(*(this->mInnerAction));
			action.Update(dt, blend);
			if (action.IsDone())
			{
				float exceed = action.ElapsedExceed();
				action.Start();
				action.Update(exceed, blend);
			}
		}
			break;
		case ActionType::Infinite:
			if (this->mInnerAction->IsDone())
			{
				this->mInnerAction->Start();
			}
			this->mInnerAction->Update(dt, blend);
			break;
		default:
			break;
	}

	return true;
}

MEDUSA_END;
