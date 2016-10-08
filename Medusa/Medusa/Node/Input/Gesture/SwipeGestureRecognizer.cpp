// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/SwipeGestureRecognizer.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Core/Math/Math.h"
#include "Node/Input/Gesture/EventArg/SwipeBeginGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeMovedGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeFailedGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeSuccessGestureEventArg.h"
#include "Core/Log/Log.h"


MEDUSA_BEGIN;
SwipeGestureRecognizer::SwipeGestureRecognizer(INode* node, ScrollDirection direction, float minMovement, float minVelocity)
	:IGestureRecognizer(node),
	mDirection(direction),
	mMinMovement(minMovement),
	mMinVelocity(minVelocity)
{
	Reset();
}


SwipeGestureRecognizer::~SwipeGestureRecognizer(void)
{

}

void SwipeGestureRecognizer::Reset()
{
	mPrevPos = Point2F::Zero;
	mCurrentPos = Point2F::Zero;
	mBeginPos = Point2F::Zero;
	mBeginTimeStamp = StopWatch::ClockType::now();
	mEndTimeStamp = mBeginTimeStamp;
	mPrevTimeStamp = mBeginTimeStamp;
}

void SwipeGestureRecognizer::TouchesBegan(TouchEventArg& e)
{
	IInputHandler::TouchesBegan(e);
	switch (mState)
	{
	case InputState::None:
		if (e.IsValid())
		{
			mBeginPos = e.GetValidActiveMiddlePoint();
			mPrevPos = mBeginPos;
			mCurrentPos = mBeginPos;
			mBeginTimeStamp = StopWatch::ClockType::now();
			mEndTimeStamp = mBeginTimeStamp;
			mPrevTimeStamp = mBeginTimeStamp;


			SetState(InputState::Begin);
			//e.Handled=true;

			//swipe begin event
			SwipeBeginGestureEventArg e2(this);
			OnSwipeBegin(mNode, e2);
		}
		break;
	default:
		break;
	}
}

void SwipeGestureRecognizer::TouchesMoved(TouchEventArg& e)
{
	IInputHandler::TouchesMoved(e);
	switch (mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
	{
		mPrevTimeStamp = mEndTimeStamp;
		mPrevPos = mCurrentPos;

		mEndTimeStamp = StopWatch::ClockType::now();
		mCurrentPos = e.GetValidActiveMiddlePoint();

		if (!IsMovementValid())
		{
			//don't move,keep prev pos and prev time stamp at begin

		}
		else
		{
			//first move
			SetState(InputState::Valid);

			SwipeMovedGestureEventArg e2(this);
			OnSwipeMoved(mNode, e2);

			e.Handled = true;
		}
	}

	break;

	case InputState::Valid:
	{
		//first move
		mPrevPos = mCurrentPos;
		mPrevTimeStamp = mEndTimeStamp;

		mEndTimeStamp = StopWatch::ClockType::now();
		mCurrentPos = e.GetValidActiveMiddlePoint();

		SwipeMovedGestureEventArg e2(this);
		OnSwipeMoved(mNode, e2);

		e.Handled = true;
	}
	break;
	default:
		break;
	}

}

void SwipeGestureRecognizer::TouchesEnded(TouchEventArg& e)
{
	IInputHandler::TouchesEnded(e);
	switch (mState)
	{
	case InputState::None:
	case InputState::Begin:
	{
		mPrevPos = mCurrentPos;
		mPrevTimeStamp = mEndTimeStamp;

		mCurrentPos = e.GetValidActiveMiddlePoint();
		mEndTimeStamp = StopWatch::ClockType::now();

		if (e.IsValid())
		{
			SetState(InputState::End);
		}
		else
		{
			SetState(InputState::Failed);
		}

		SwipeFailedGestureEventArg e2(this);
		OnSwipeFailed(mNode, e2);
	}
	break;
	case InputState::Valid:
	{
		mPrevPos = mCurrentPos;
		mPrevTimeStamp = mEndTimeStamp;

		mCurrentPos = e.GetValidActiveMiddlePoint();
		mEndTimeStamp = StopWatch::ClockType::now();

		Point2F totalMovement = TotalMovement();
		Point2F velocity = VelocityAverage();


		ScrollDirection directionSucceed;
		if (IsAllowHorizontal())
		{
			if (Math::Abs(totalMovement.X)>mMinMovement || velocity.X>mMinVelocity)
			{
				directionSucceed |= ScrollDirection::HorizontalMask;
			}
		}

		if (IsAllowVertical())
		{
			if (Math::Abs(totalMovement.Y)>mMinMovement || velocity.Y>mMinVelocity)
			{
				directionSucceed |= ScrollDirection::HorizontalMask;
			}
		}


		SetState(InputState::End);

		if (directionSucceed != ScrollDirection::None)
		{
			SwipeSuccessGestureEventArg e2(this, directionSucceed);
			OnSwipeSuccess(mNode, e2);
		}
		else
		{
			SwipeFailedGestureEventArg e2(this);
			OnSwipeFailed(mNode, e2);
		}

	}
	break;
	default:
		break;
	}

	Reset();
	mState = InputState::None;
}

void SwipeGestureRecognizer::TouchesCancelled(TouchEventArg& e)
{
	IInputHandler::TouchesCancelled(e);
	Reset();
	mState = InputState::None;
}


Point2F SwipeGestureRecognizer::VelocityAverage() const
{
	Point2F movement = TotalMovement();

	float dt = TotalDuration();
	if (dt>0.000001f)
	{
		return movement / dt;
	}

	return mpp(Math::FloatMaxValue, Math::FloatMaxValue);
}


Point2F SwipeGestureRecognizer::Movement() const
{
	return mCurrentPos - mPrevPos;
}

Point2F SwipeGestureRecognizer::MovementOnDirection() const
{
	Point2F movement = Movement();
	if (!mDirection.HasHorizontal())
	{
		movement.X = 0.f;
	}

	if (!mDirection.HasVertical())
	{
		movement.Y = 0.f;
	}
	return movement;
}

Point2F SwipeGestureRecognizer::TotalMovement() const
{
	return mCurrentPos - mBeginPos;
}

Point2F SwipeGestureRecognizer::TotalMovementOnDirection() const
{
	Point2F movement = TotalMovement();
	if (!mDirection.HasHorizontal())
	{
		movement.X = 0.f;
	}

	if (!mDirection.HasVertical())
	{
		movement.Y = 0.f;
	}
	return movement;
}

bool SwipeGestureRecognizer::IsValid() const
{
	switch (mState)
	{
	case InputState::Valid:
		return true;
	default:
		return false;
	}
}

Point2F SwipeGestureRecognizer::CurrentVelocity() const
{
	return Movement() / Duration();
}


Point2F SwipeGestureRecognizer::CurrentVelocityOnDirection() const
{
	return MovementOnDirection() / Duration();
}

bool SwipeGestureRecognizer::IsMovementValid() const
{
	Point2F totalMovement = TotalMovement();

	if (IsAllowHorizontal())
	{
		if (Math::Abs(totalMovement.X)>mMinMovement)
		{
			return true;
		}
	}

	if (IsAllowVertical())
	{
		if (Math::Abs(totalMovement.Y)>mMinMovement)
		{
			return true;
		}
	}

	return false;
}

float SwipeGestureRecognizer::TotalDuration() const
{
	return StopWatch::ToMilliseconds(mEndTimeStamp - mBeginTimeStamp);
}

float SwipeGestureRecognizer::Duration() const
{
	return StopWatch::ToMilliseconds(mEndTimeStamp - mPrevTimeStamp);
}


MEDUSA_END;
