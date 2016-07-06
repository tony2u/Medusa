// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/TapGestureRecognizer.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/Gesture/EventArg/TapGestureEventArg.h"
#include "Audio/AudioEngine.h"

MEDUSA_BEGIN;
TapGestureRecognizer::TapGestureRecognizer( INode* node) 
	:IGestureRecognizer(node)
{
	mBeganTouch=Touch::Zero;
}


TapGestureRecognizer::~TapGestureRecognizer(void)
{
	mNode=nullptr;
}

void TapGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	IInputHandler::TouchesBegan(e);
	switch(mState)
	{
	case InputState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.FirstValidActiveTouch();
			SetState(InputState::Begin);
			if (MEDUSA_FLAG_HAS(mBehaviors,InputBehaviors::SuppressTouchBegan))
			{
				e.Handled=true;
			}
		}
		break;
	case InputState::Begin:
		break;
	default:
		break;
	}

}

void TapGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	IInputHandler::TouchesMoved(e);
	switch(mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
		{
			if (!e.IsValid())
			{
				SetState(InputState::Failed);
				mBeganTouch=Touch::Zero;
				//e.Handled=true;

			}
		}
		break;
	default:
		break;
	}

}

void TapGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	IInputHandler::TouchesEnded(e);
	switch(mState)
	{
	case InputState::None:
		OnTapFailed(mNode);
		break;
	case InputState::Begin:
		{
			if (e.IsValid()&&e.FindValidActiveTouchById(mBeganTouch.Id)!=nullptr)
			{
				if (MEDUSA_FLAG_HAS(mBehaviors,InputBehaviors::PlayAudio))
				{
#ifdef MEDUSA_AL
					AudioEngine::Instance().PlayEffect(mAudioEffect.ToRef());
#endif
				}

				SetState(InputState::Valid);
				TapGestureEventArg tapEventArg(this,e.FirstValidActiveTouch());
				OnTap(mNode,tapEventArg);
				RaiseEvent(InputEventType::Tap, &tapEventArg);
				SetState(InputState::None);
				mBeganTouch=Touch::Zero;
				e.Handled=true;
				CancelOtherHandlers();

			}
		}
		break;
	default:
		break;
	}

	SetState(InputState::None);
}

void TapGestureRecognizer::MockTouch( TouchEventArg& e )
{
	if (e.IsValid())
	{
		TapGestureEventArg tapEventArg(this,e.FirstValidActiveTouch());
		OnTap(mNode,tapEventArg);
		RaiseEvent(InputEventType::Tap,&tapEventArg);
		e.Handled=tapEventArg.Handled;
	}
}

void TapGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	IInputHandler::TouchesCancelled(e);
	SetState(InputState::None);
}

bool TapGestureRecognizer::IsValid() const
{
	return mState==InputState::Valid;
}

void TapGestureRecognizer::Reset()
{
	SetState(InputState::None);
}



MEDUSA_END;