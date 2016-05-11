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
PanGestureRecognizer::PanGestureRecognizer( INode* node, float minDistance) 
	:IGestureRecognizer(node)
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
	IInputHandler::TouchesBegan(e);
	switch(mState)
	{
	case InputState::None:
		if (e.IsValid())
		{
			mTouchEventArg.MergeValidActiveTouches(e);

			mCurCenter = mTouchEventArg.GetValidActiveMiddlePoint();
			SetState(InputState::Begin);
			PanBeginGestureEventArg t(this);
			OnBegin(mNode,t);
		}
		break;
	case InputState::Begin:
	case InputState::Valid:
		if (e.IsValid())
		{
			mTouchEventArg.MergeValidActiveTouches(e);

			mCurCenter = mTouchEventArg.GetValidActiveMiddlePoint();
			SetState(InputState::Begin);
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
	IInputHandler::TouchesMoved(e);
	switch(mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
	case InputState::Recognizing:
		{
			mTouchEventArg.MoveValidActiveTouches(e);

			Point2F curCenter = mTouchEventArg.GetValidActiveMiddlePoint();
			mMovement = curCenter - mCurCenter;
			float distance =mMovement.Length();
			if (distance > mMinDistance)
			{
				// Valid
				SetState(InputState::Valid);
				mCurCenter = curCenter;
				e.Handled=true;
				PanGestureEventArg t(this,mMovement);
				OnPan(mNode,t);
				CancelOtherHandlers();
			}
			else
			{
				// Recognizing
				SetState(InputState::Recognizing);
				mMovement = Point2F::Zero;
			}
		}
		break;
	case InputState::Valid:
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
	IInputHandler::TouchesEnded(e);
	mTouchEventArg.RemoveValidActiveTouches(e);

	switch(mState)
	{
	case InputState::None:
		{
			mState=InputState::Failed;
			Reset();
			PanEndGestureEventArg t(this);
			OnEnd(mNode,t);
		}
		break;
	case InputState::Begin:
	case InputState::Recognizing:
	case InputState::Valid:
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
	IInputHandler::TouchesCancelled(e);
	Reset();
}

bool PanGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case InputState::Valid:
		return true;
	default:
		return false;
	}
}


void PanGestureRecognizer::Reset()
{
	SetState(InputState::None);
	mMovement = Point2F::Zero;
	mCurCenter = Point2F::Zero;
	mTouchEventArg.Clear();
}


MEDUSA_END;