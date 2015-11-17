// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseSingleCompositeInfiniteAction.h"
#include "Core/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;
class RepeatedForeverAction :public BaseSingleCompositeInfiniteAction
{
public:
	RepeatedForeverAction(IAction* innerAction) :BaseSingleCompositeInfiniteAction(innerAction) {}
	virtual ~RepeatedForeverAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override;

	static RepeatedForeverAction* Create(IAction* innerAction)
	{
		return new RepeatedForeverAction(innerAction);
	}

};
MEDUSA_END;
