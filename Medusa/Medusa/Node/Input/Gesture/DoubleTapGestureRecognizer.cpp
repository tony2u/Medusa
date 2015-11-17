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
DoubleTapGestureRecognizer::DoubleTapGestureRecognizer( INode* node ,float maxDuration/*=0.25f*/,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags),mMaxDuration(maxDuration)
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
	switch(mState)
	{
	case GestureState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.FirstValidActiveTouch();
			SetState(GestureState::Begin);
		}
		break;
	case GestureState::Begin:
		break;
	case GestureState::Recognizing:
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
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
		{
			if (!e.IsValid())
			{
				SetState(GestureState::Failed);
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
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		{
			if (e.IsValid()&&e.FindValidActiveTouchById(mBeganTouch.Id)!=nullptr)
			{
				mFirstSuccessTouch=*e.FindValidActiveTouchById(mBeganTouch.Id);
				SetState(GestureState::Recognizing);
				mBeganTouch=Touch::Zero;
				e.Handled=true;
				CancelOtherHandlers();
				mBeginTimeStamp=Application::Instance().TimeStamp();
				return;	//DO NOT set to none
			}
			break;
		}
	case GestureState::Recognizing:
		{

			if (e.IsValid() && e.FindValidActiveTouchById(mBeganTouch.Id) != nullptr)
			{
				SetState(GestureState::Valid);
				double timeStamp = Application::Instance().TimeStamp()-mBeginTimeStamp;
				if (timeStamp <= mMaxDuration)
				{
					DoubleTapGestureEventArg tapEventArg(this, e.FirstValidActiveTouch(), (float)timeStamp);
					OnDoubleTap(mNode, tapEventArg);
					SetState(GestureState::None);
					mBeganTouch = Touch::Zero;
				}
				else
				{
					SetState(GestureState::None);
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

	SetState(GestureState::None);

}

void DoubleTapGestureRecognizer::TryFireEvent( TouchEventArg& e )
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
	SetState(GestureState::None);
	Reset();
}

bool DoubleTapGestureRecognizer::IsValid() const
{
	return mState==GestureState::Valid;
}

void DoubleTapGestureRecognizer::Reset()
{
	SetState(GestureState::None);
	mBeginTimeStamp=0.f;
	mBeganTouch=Touch::Zero;
	mFirstSuccessTouch=Touch::Zero;

}


MEDUSA_END;