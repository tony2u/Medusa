// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
#include "Core/Geometry/Point3.h"
MEDUSA_BEGIN;

template<typename T>
class TMoveByAction:public BaseFiniteAction
{
public:
	TMoveByAction(const Point3F& delta, float duration) :BaseFiniteAction(duration), mDelta(delta) 
	{

	}
	virtual ~TMoveByAction(void) {}
public:
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		Point3F delta = mDelta*(dt / mDuration *blend);
		T* node = (T*)mTarget;
		node->SetPosition(node->Position() + delta);
		return true;
	}

	virtual TMoveByAction* Clone()const override
	{
		return new TMoveByAction(mDelta, mDuration);

	}
	virtual TMoveByAction* Reverse()const override
	{
		return new TMoveByAction(-mDelta, mDuration);
	}

	static TMoveByAction* Create(const Point3F& delta, float duration)
	{
		return new TMoveByAction(delta, duration);

	}
private:
	Point3F mDelta;
};

//[PRE_DECLARE_BEGIN]
typedef TMoveByAction<INode> MoveByAction;
//[PRE_DECLARE_END]

MEDUSA_END;
