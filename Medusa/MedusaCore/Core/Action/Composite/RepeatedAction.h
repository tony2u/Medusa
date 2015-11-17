// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseSingleCompositeInfiniteAction.h"
#include "Core/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;
class RepeatedAction :public BaseSingleCompositeInfiniteAction
{
public:
	RepeatedAction(IAction* innerAction, int count) :BaseSingleCompositeInfiniteAction(innerAction), mCount(count) {}
	virtual ~RepeatedAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override;

	static RepeatedAction* Create(IAction* innerAction, int count)
	{
		return new RepeatedAction(innerAction, count);
	}
private:
	int mCount;
};
MEDUSA_END;
