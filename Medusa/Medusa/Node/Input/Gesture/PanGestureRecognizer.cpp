// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/PanGestureRecognizer.h"
#include "Node/Input/Gesture/EventArg/PanGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/PanBeginGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/PanEndGestureEventArg.h"

#include "Node/Input/EventArg/TouchEventArg.h"

MEDUSA_BEGIN;
PanGestureRecognizer::PanGestureRecognizer( INode* node, float minDistance,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags)
{
	Reset();
	mMinDistance = minDistance;
}


PanGestureRecognizer::~PanGestureRecognizer(void)
{
	mNode = nullptr;
}

void PanGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsValid())
		{
			mTouchEventArg.MergeValidActiveTouches(e);

			mCurCenter = mTouchEventArg.GetValidActiveMiddlePoint();
			SetState(GestureState::Begin);
			PanBeginGestureEventArg t(this);
			OnBegin(mNode,t);
		}
		break;
	case GestureState::Begin:
	case GestureState::Valid:
		if (e.IsValid())
		{
			mTouchEventArg.MergeValidActiveTouches(e);

			mCurCenter = mTouchEventArg.GetValidActiveMiddlePoint();
			SetState(GestureState::Begin);
			PanBeginGestureEventArg t(this);
			OnBegin(mNode,t);
		}
		break;
	default:
		break;
	}

}

void PanGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
		{
			mTouchEventArg.MoveValidActiveTouches(e);

			Point2F curCenter = mTouchEventArg.GetValidActiveMiddlePoint();
			mMovement = curCenter - mCurCenter;
			float distance =mMovement.Length();
			if (distance > mMinDistance)
			{
				// Valid
				SetState(GestureState::Valid);
				mCurCenter = curCenter;
				e.Handled=true;
				PanGestureEventArg t(this,mMovement);
				OnPan(mNode,t);
				CancelOtherHandlers();
			}
			else
			{
				// Recognizing
				SetState(GestureState::Recognizing);
				mMovement = Point2F::Zero;
			}
		}
		break;
	case GestureState::Valid:
		{
			mTouchEventArg.MoveValidActiveTouches(e);

			Point2F curCenter = mTouchEventArg.GetValidActiveMiddlePoint();
			mMovement = curCenter - mCurCenter;
			mCurCenter = curCenter;
			e.Handled=true;
			PanGestureEventArg t(this,mMovement);
			OnPan(mNode,t);
			CancelOtherHandlers();

		}
		break;
	default:
		break;
	}
}

void PanGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	mTouchEventArg.RemoveValidActiveTouches(e);

	switch(mState)
	{
	case GestureState::None:
		{
			mState=GestureState::Failed;
			Reset();
			PanEndGestureEventArg t(this);
			OnEnd(mNode,t);
		}
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
	case GestureState::Valid:
		{
			Reset();
			PanEndGestureEventArg t(this);
			OnEnd(mNode,t);
		}
		break;
	default:
		break;
	}

}

void PanGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	Reset();
}

bool PanGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case GestureState::Valid:
		return true;
	default:
		return false;
	}
}


void PanGestureRecognizer::Reset()
{
	SetState(GestureState::None);
	mMovement = Point2F::Zero;
	mCurCenter = Point2F::Zero;
	mTouchEventArg.Clear();
}


MEDUSA_END;