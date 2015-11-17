// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"
#include "Core/Geometry/ScrollDirection.h"
#include "Core/Profile/PerformanceCounter.h"

MEDUSA_BEGIN;


class SwipeGestureRecognizer:public IGestureRecognizer
{
public:
	SwipeGestureRecognizer(INode* node, ScrollDirection direction, float minMovement, float minVelocity, GestureFlags flags = GestureFlags::None);
	virtual ~SwipeGestureRecognizer(void);

	virtual void Reset();

	virtual InputType GetInputType()const{return InputType::Swipe;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual bool IsValid()const;

	const Point2F& PrevPos() const { return mPrevPos; }
	const Point2F& CurPos() const { return mCurrentPos; }
	const Point2F& BeginPos() const { return mBeginPos; }

	Point2F Movement()const;
	Point2F MovementOnDirection()const;

	Point2F TotalMovement()const;
	Point2F TotalMovementOnDirection()const;

	float TotalDuration()const;
	float Duration()const;


	Point2F VelocityAverage()const;
	Point2F CurrentVelocity() const;
	Point2F CurrentVelocityOnDirection() const;


	ScrollDirection Direction() const { return mDirection; }
	void SetDirection(ScrollDirection val) { mDirection = val; }

	bool IsAllowHorizontal()const{return mDirection.HasHorizontal();}
	bool IsAllowVertical()const{return mDirection.HasVertical();}


	virtual bool HasHandler()const{return !OnSwipeBegin.IsEmpty()||!OnSwipeMoved.IsEmpty()||!OnSwipeFailed.IsEmpty()||!OnSwipeSuccess.IsEmpty();}

	SwipeBeginEvent OnSwipeBegin;
	SwipeMovedEvent OnSwipeMoved;
	SwipeFailedEvent OnSwipeFailed;
	SwipeSuccessEvent OnSwipeSuccess;
protected:
	bool IsMovementValid()const;

private:
	Point2F mPrevPos;
	Point2F mCurrentPos;
	Point2F mBeginPos;
	ScrollDirection mDirection;
	
	ProfileTimeType mPrevTimeStamp;
	ProfileTimeType mBeginTimeStamp;
	ProfileTimeType mEndTimeStamp;

	float mMinMovement;
	float mMinVelocity;
};



MEDUSA_END;