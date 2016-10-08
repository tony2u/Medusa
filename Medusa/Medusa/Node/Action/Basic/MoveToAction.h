// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
#include "Geometry/Point3.h"

MEDUSA_BEGIN;


//move action interface
//Point3F Position()const;
//void SetPosition(const Point3F& val);

template<typename T>
class TMoveToAction :public BaseFiniteAction
{
public:
	TMoveToAction(const Point3F& endPosition, float duration)
		:BaseFiniteAction(duration),
		mBeginPosition(Point3F::Zero),
		mEndPosition(endPosition),
		mDelta(endPosition)
	{

	}

	TMoveToAction(const Point3F& beginPosition, const Point3F& endPosition, float duration)
		:BaseFiniteAction(duration),
		mBeginPosition(beginPosition),
		mEndPosition(endPosition),
		mDelta(endPosition - beginPosition)
	{

	}

	TMoveToAction(float duration)
		:BaseFiniteAction(duration),
		mBeginPosition(Point3F::Zero),
		mEndPosition(Point3F::Zero),
		mDelta(Point3F::Zero)
	{
		// set end position later
	}

	virtual ~TMoveToAction(void)
	{

	}
public:
	Point3F EndPosition() const { return mEndPosition; }
	void SetEndPosition(Point3F val) { mEndPosition = val; }

	virtual bool Start()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Start());
		T* node = (T*)mTarget;
		mBeginPosition = node->Position();
		mDelta = mEndPosition - mBeginPosition;

		return true;
	}

	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Reset());
		T* node = (T*)mTarget;

		mBeginPosition = node->Position();
		mDelta = mEndPosition - mBeginPosition;
		return true;
	}
	virtual bool Update(float dt, float blend = 1.f)override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
		Point3F delta = mDelta*(Percent()*blend);
		T* node = (T*)mTarget;

		node->SetPosition(mBeginPosition + delta);
		return true;
	}

public:
	virtual TMoveToAction* Clone()const override
	{
		return new TMoveToAction(mBeginPosition, mEndPosition, this->mDuration);

	}
	virtual TMoveToAction* Reverse()const override
	{
		return new TMoveToAction(mEndPosition, mBeginPosition, this->mDuration);
	}

	static TMoveToAction* Create(const Point3F& position, float duration)
	{
		return new TMoveToAction(position, duration);
	}
private:
	Point3F mBeginPosition;
	Point3F mEndPosition;
	
	Point3F mDelta;
};

//[PRE_DECLARE_BEGIN]
typedef TMoveToAction<INode> MoveToAction;
//[PRE_DECLARE_END]

MEDUSA_END;
