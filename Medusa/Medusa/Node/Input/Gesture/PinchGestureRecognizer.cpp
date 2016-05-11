// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/PinchGestureRecognizer.h"
#include "Node/INode.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/Gesture/EventArg/PinchGestureEventArg.h"


MEDUSA_BEGIN;
PinchGestureRecognizer::PinchGestureRecognizer( INode* node) 
	:IGestureRecognizer(node)
{
	Reset();
}

PinchGestureRecognizer::~PinchGestureRecognizer(void)
{
	mNode = nullptr;
}

void PinchGestureRecognizer::TouchesBegan(TouchEventArg& e)
{
	IInputHandler::TouchesBegan(e);
	switch(mState)
	{
	case InputState::None:
	case InputState::Recognizing:
		mTouchEventArg.MergeValidActiveTouches(e);
		if (mTouchEventArg.ValidTouchActiveCount()<2)
		{
			SetState(InputState::Recognizing);
		}
		else
		{
			SetState(InputState::Begin);
			const List<Touch>& touches=mTouchEventArg.ValidActiveTouches();
			mPinchEndDistance = mPinchBeginDistance = Point2F::Distance(touches[0].Pos,touches[1].Pos);
		}
		break;
	case InputState::Begin:
	case InputState::Valid:
		
		break;
	default:
		break;
	}



}

void PinchGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	IInputHandler::TouchesMoved(e);
	switch(mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
	case InputState::Valid:
		{
			mTouchEventArg.MoveValidActiveTouches(e);

			SetState(InputState::Valid);
			mPinchBeginDistance = mPinchEndDistance;
			const List<Touch>& touches=mTouchEventArg.ValidActiveTouches();
			mPinchEndDistance = Point2F::Distance(touches[0].Pos,touches[1].Pos);

			//reset anchor
			Point2F p1 = touches[0].Pos;
			Point2F p2 = touches[1].Pos;
			Point2F middlePoint = p1 + (p2 - p1) * 0.5f;

			PinchGestureEventArg t(this,GetScaleFactor(),middlePoint);
			OnPinch(mNode,t);

			e.Handled=true;
			CancelOtherHandlers();

		}
		break;
	default:
		break;
	}


}

void PinchGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	IInputHandler::TouchesEnded(e);
	mTouchEventArg.RemoveValidActiveTouches(e);
	switch(mState)
	{
	case InputState::None:
	case InputState::Recognizing:
		{
			mState=InputState::Failed;
			Reset();
		}
		break;
	case InputState::Begin:
	case InputState::Valid:
		{
			if (mTouchEventArg.ValidTouchActiveCount() == 0)
			{
				SetState(InputState::End);
				Reset();
			}
			else if (mTouchEventArg.ValidTouchActiveCount() == 1)
			{
				SetState(InputState::Recognizing);
			}
		}
		break;
	default:
		break;
	}


}

void PinchGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	IInputHandler::TouchesCancelled(e);
	mState=InputState::None;
	Reset();
}

bool PinchGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case InputState::Valid:
		return true;
	default:
		return false;
	}
}

void PinchGestureRecognizer::Reset()
{
	SetState(InputState::None);
	mPinchEndDistance = 0.f;
	mPinchBeginDistance = 0.f;
	mTouchEventArg.Clear();
}


MEDUSA_END;