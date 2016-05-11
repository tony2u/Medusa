// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/LongPressGestureRecognizer.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/Gesture/EventArg/LongPressBeganGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/LongPressFailedGestureEventArg.h"
MEDUSA_BEGIN;
LongPressGestureRecognizer::LongPressGestureRecognizer( INode* node,float minPressDuration,float allowMovement) 
	:IGestureRecognizer(node)
{
	mMinPressDuration=minPressDuration;
	mAllowMovement=allowMovement;
	mBeginTimeStamp=0.f;
	mState=InputState::None;
	mBeganTouch=Touch::Zero;
}


LongPressGestureRecognizer::~LongPressGestureRecognizer(void)
{
	mNode=nullptr;
}


void LongPressGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	IInputHandler::TouchesBegan(e);
	switch(mState)
	{
	case InputState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.FirstValidActiveTouch();
			mBeginTimeStamp=0.f;
			SetState(InputState::Begin);
		}
		break;
	case InputState::Valid:
		break;
	default:
		break;
	}

}

void LongPressGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	IInputHandler::TouchesMoved(e);
	switch(mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
		{
			auto nextTouch=e.FindValidActiveTouchById(mBeganTouch.Id);
			if (nextTouch!=nullptr)
			{
				float distance=Point2F::Distance(mBeganTouch.Pos,nextTouch->Pos);
				if (distance>mAllowMovement)
				{
					SetState(InputState::None);
				}
			}
		}

		break;
	case InputState::Valid:
		break;
	default:
		break;
	}
	
}

void LongPressGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	IInputHandler::TouchesEnded(e);
	switch(mState)
	{
	case InputState::None:
	case InputState::Begin:
		{
			SetState(InputState::Failed);

			LongPressFailedGestureEventArg longPressFailedGestureEventArg(this);
			OnLongPressFailed(mNode,longPressFailedGestureEventArg);
			e.Handled=longPressFailedGestureEventArg.Handled;
		}

		break;
	case InputState::Valid:
		{
			SetState(InputState::End);
		}
		
		break;
	default:
		break;
	}

	SetState(InputState::None);

}

void LongPressGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	IInputHandler::TouchesCancelled(e);
	SetState(InputState::None);
}

bool LongPressGestureRecognizer::Update( float dt )
{
	switch(mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
		mBeginTimeStamp+=dt;
		if (mBeginTimeStamp>mMinPressDuration)
		{
			SetState(InputState::Valid);
			mBeginTimeStamp=0.f;

			LongPressBeganGestureEventArg longPressBeganGestureEventArg(this);
			OnLongPressBegan(mNode,longPressBeganGestureEventArg);
			CancelOtherHandlers();

		}

		break;
	case InputState::Valid:

	default:
		break;
	}

	return true;

}

void LongPressGestureRecognizer::Reset()
{
	mBeginTimeStamp=0.f;
	SetState(InputState::None);
	mBeganTouch=Touch::Zero;
}

bool LongPressGestureRecognizer::IsValid() const
{
	return mState==InputState::Valid;
}

MEDUSA_END;