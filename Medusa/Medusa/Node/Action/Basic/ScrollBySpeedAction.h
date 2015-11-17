// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInfiniteAction.h"
#include "Core/Geometry/Point2.h"

MEDUSA_BEGIN;

template<typename T>
class TScrollBySpeedAction:public BaseInfiniteAction
{
public:
	TScrollBySpeedAction(const Point2F& speed) :BaseInfiniteAction(), mSpeed(speed) {}
	virtual ~TScrollBySpeedAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt, blend));
		T* node = (T*)mTarget;
		node->ScrollBy(mSpeed*dt);
		return true;
	}

	virtual TScrollBySpeedAction* Clone()const override
	{
		return new TScrollBySpeedAction(mSpeed);

	}
	virtual TScrollBySpeedAction* Reverse()const override
	{
		return new TScrollBySpeedAction(-mSpeed);
	}

	static TScrollBySpeedAction* Create(Point2F speed)
	{
		return new TScrollBySpeedAction(speed);
	}
private:
	Point2F mSpeed;
};

MEDUSA_END;
