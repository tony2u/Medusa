// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
#include "Geometry/Point2.h"
MEDUSA_BEGIN;

template<typename T>
class TScrollByAction:public BaseFiniteAction
{
public:
	TScrollByAction(const Point2F& delta, float duration) :BaseFiniteAction(duration), mDelta(delta) 
	{

	}
	virtual ~TScrollByAction(void) {}
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		Point2F delta = mDelta*(dt / mDuration *blend);
		T* node = (T*)mTarget;
		node->ScrollBy(delta);
		return true;
	}

	virtual TScrollByAction* Clone()const override
	{
		return new TScrollByAction(mDelta, mDuration);

	}
	virtual TScrollByAction* Reverse()const override
	{
		return new TScrollByAction(-mDelta, mDuration);
	}

	static TScrollByAction* Create(const Point2F& delta, float duration)
	{
		return new TScrollByAction(delta, duration);

	}
private:
	Point2F mDelta;
};


MEDUSA_END;
