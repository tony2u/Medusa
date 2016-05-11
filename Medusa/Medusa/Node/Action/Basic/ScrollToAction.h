// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
#include "Geometry/Point2.h"

MEDUSA_BEGIN;


template<typename T>
class TScrollToAction:public BaseFiniteAction
{
public:
	TScrollToAction(const Point2F& endPosition, float duration)
		:BaseFiniteAction(duration),
		mEndPosition(endPosition),
		mBeginPosition(Point2F::Zero),
		mDelta(endPosition)
	{

	}

	virtual ~TScrollToAction(void)
	{

	}
public:
	virtual bool Start()
	{
		T* node = (T*)mTarget;
		mBeginPosition = node->Offset();
		mDelta = mEndPosition - mBeginPosition;
		return true;
	}

	virtual bool Reset()
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Reset());
		T* node = (T*)mTarget;

		mBeginPosition = node->Offset();
		mDelta = mEndPosition - mBeginPosition;
		return true;
	}
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		Point2F delta = mDelta*(Percent()*blend);
		T* node = (T*)mTarget;

		node->ScrollTo(mBeginPosition + delta);
		return true;
	}
public:
	virtual TScrollToAction* Clone()const override
	{
		return new TScrollToAction(mEndPosition, this->mDuration);

	}
	virtual TScrollToAction* Reverse()const override
	{
		return new TScrollToAction(mEndPosition,this->mDuration);
	}

	static TScrollToAction* Create(const Point2F& position, float duration)
	{
		return new TScrollToAction(position, duration);
	}
private:
	Point2F mBeginPosition;
	Point2F mEndPosition;
	Point2F mDelta;
};


MEDUSA_END;
