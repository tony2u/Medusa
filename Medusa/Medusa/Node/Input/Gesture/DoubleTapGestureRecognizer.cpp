// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/DoubleTapGestureRecognizer.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/Gesture/EventArg/TapGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DoubleTapGestureEventArg.h"
#include "Application/Application.h"

MEDUSA_BEGIN;
DoubleTapGestureRecognizer::DoubleTapGestureRecognizer( INode* node ,float maxDuration/*=0.25f*/) 
	:IGestureRecognizer(node),mMaxDuration(maxDuration)
{
	mBeganTouch=Touch::Zero;
	mFirstSuccessTouch=Touch::Zero;
}


DoubleTapGestureRecognizer::~DoubleTapGestureRecognizer(void)
{
	mNode=nullptr;
}

void DoubleTapGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	IInputHandler::TouchesBegan(e);
	switch(mState)
	{
	case InputState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.FirstValidActiveTouch();
			SetState(InputState::Begin);
		}
		break;
	case InputState::Begin:
		break;
	case InputState::Recognizing:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.FirstValidActiveTouch();
		}
		break;
	default:
		break;
	}

}

void DoubleTapGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	IInputHandler::TouchesMoved(e);
	switch(mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
	case InputState::Recognizing:
		{
			if (!e.IsValid())
			{
				SetState(InputState::Failed);
				mBeganTouch=Touch::Zero;
			}
		}
		break;
	default:
		break;
	}

}

void DoubleTapGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	IInputHandler::TouchesEnded(e);
	switch(mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
		{
			if (e.IsValid()&&e.FindValidActiveTouchById(mBeganTouch.Id)!=nullptr)
			{
				mFirstSuccessTouch=*e.FindValidActiveTouchById(mBeganTouch.Id);
				SetState(InputState::Recognizing);
				mBeganTouch=Touch::Zero;
				e.Handled=true;
				CancelOtherHandlers();
				mBeginTimeStamp=Application::Instance().TimeStamp();
				return;	//DO NOT set to none
			}
			break;
		}
	case InputState::Recognizing:
		{

			if (e.IsValid() && e.FindValidActiveTouchById(mBeganTouch.Id) != nullptr)
			{
				SetState(InputState::Valid);
				double timeStamp = Application::Instance().TimeStamp()-mBeginTimeStamp;
				if (timeStamp <= mMaxDuration)
				{
					DoubleTapGestureEventArg tapEventArg(this, e.FirstValidActiveTouch(), (float)timeStamp);
					OnDoubleTap(mNode, tapEventArg);
					SetState(InputState::None);
					mBeganTouch = Touch::Zero;
				}
				else
				{
					SetState(InputState::None);
					mBeginTimeStamp = 0.f;
					TapGestureEventArg tapEventArg(this, mFirstSuccessTouch);
					OnTap(mNode, tapEventArg);
				}
				
				mFirstSuccessTouch = Touch::Zero;
			}
			e.Handled=true;
			CancelOtherHandlers();
		}
		break;
	default:
		break;
	}

	SetState(InputState::None);

}

void DoubleTapGestureRecognizer::MockTouch( TouchEventArg& e )
{
	
	if (e.IsValid())
	{
		double timeStamp = Application::Instance().TimeStamp() - mBeginTimeStamp;
		DoubleTapGestureEventArg tapEventArg(this, e.FirstValidActiveTouch(), (float)timeStamp);
		OnDoubleTap(mNode,tapEventArg);
		e.Handled=tapEventArg.Handled;
	}
}

void DoubleTapGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	IInputHandler::TouchesCancelled(e);
	SetState(InputState::None);
	Reset();
}

bool DoubleTapGestureRecognizer::IsValid() const
{
	return mState==InputState::Valid;
}

void DoubleTapGestureRecognizer::Reset()
{
	SetState(InputState::None);
	mBeginTimeStamp=0.f;
	mBeganTouch=Touch::Zero;
	mFirstSuccessTouch=Touch::Zero;

}


MEDUSA_END;