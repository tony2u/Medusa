// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
#include "Geometry/Point2.h"

MEDUSA_BEGIN;


template<typename T>
class TScrollToPageAction:public BaseFiniteAction
{
public:
	TScrollToPageAction(const Point2F& endPosition, float duration)
		:BaseFiniteAction(duration),
		mEndPosition(endPosition),
		mBeginPosition(Point2F::Zero),
		mDelta(endPosition)
	{

	}

	virtual ~TScrollToPageAction(void)
	{

	}
public:
	virtual bool Start()
	{
		T* node = (T*)mTarget;
		mBeginPosition = node->Page();
		mDelta = mEndPosition - mBeginPosition;
		return true;
	}

	virtual bool Reset()
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Reset());
		T* node = (T*)mTarget;

		mBeginPosition = node->Page();
		mDelta = mEndPosition - mBeginPosition;
		return true;
	}
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		Point2F delta = mDelta*(Percent()*blend);
		T* node = (T*)mTarget;

		node->ScrollToPage(mBeginPosition + delta);
		return true;
	}

public:
	virtual TScrollToPageAction* Clone()const override
	{
		return new TScrollToPageAction(mEndPosition, this->mDuration);

	}
	virtual TScrollToPageAction* Reverse()const override
	{
		return new TScrollToPageAction(mEndPosition,this->mDuration);
	}

	static TScrollToPageAction* Create(const Point2F& position, float duration)
	{
		return new TScrollToPageAction(position, duration);
	}
private:
	Point2F mBeginPosition;
	Point2F mEndPosition;
	Point2F mDelta;
};


MEDUSA_END;
