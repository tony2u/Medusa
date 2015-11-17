// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInfiniteAction.h"
#include "Core/Geometry/Point3.h"

MEDUSA_BEGIN;

template<typename T>
class TMoveBySpeedAction:public BaseInfiniteAction
{
public:
	TMoveBySpeedAction(const Point3F& speed) :BaseInfiniteAction(), mSpeed(speed) {}
	virtual ~TMoveBySpeedAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt, blend));
		T* node = (T*)mTarget;
		node->Move(mSpeed*dt);
		return true;
	}

	virtual TMoveBySpeedAction* Clone()const override
	{
		return new TMoveBySpeedAction(mSpeed);

	}
	virtual TMoveBySpeedAction* Reverse()const override
	{
		return new TMoveBySpeedAction(-mSpeed);
	}

	static TMoveBySpeedAction* Create(Point3F speed)
	{
		return new TMoveBySpeedAction(speed);
	}
private:
	Point3F mSpeed;
};


//[PRE_DECLARE_BEGIN]
typedef TMoveBySpeedAction<INode> MoveBySpeedAction;
//[PRE_DECLARE_END]
MEDUSA_END;
