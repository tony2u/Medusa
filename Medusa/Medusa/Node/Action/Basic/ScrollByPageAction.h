// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
#include "Geometry/Point2.h"
MEDUSA_BEGIN;

template<typename T>
class TScrollByPageAction:public BaseFiniteAction
{
public:
	TScrollByPageAction(const Point2F& delta, float duration) :BaseFiniteAction(duration), mDelta(delta) 
	{

	}
	virtual ~TScrollByPageAction(void) {}
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		Point2F delta = mDelta*(dt / mDuration *blend);
		T* node = (T*)mTarget;
		node->ScrollByPage(delta);
		return true;
	}

	virtual TScrollByPageAction* Clone()const override
	{
		return new TScrollByPageAction(mDelta, mDuration);

	}
	virtual TScrollByPageAction* Reverse()const override
	{
		return new TScrollByPageAction(-mDelta, mDuration);
	}

	static TScrollByPageAction* Create(const Point2F& delta, float duration)
	{
		return new TScrollByPageAction(delta, duration);

	}
private:
	Point2F mDelta;
};


MEDUSA_END;
