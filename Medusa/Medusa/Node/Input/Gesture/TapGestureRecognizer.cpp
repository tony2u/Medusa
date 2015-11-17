// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/TapGestureRecognizer.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/Gesture/EventArg/TapGestureEventArg.h"
#include "Audio/AudioEngine.h"

MEDUSA_BEGIN;
TapGestureRecognizer::TapGestureRecognizer( INode* node ,GestureFlags flags/*=GestureFlags::None*/,const FileIdRef& audioEffect/*=FileId::Empty*/) 
	:IGestureRecognizer(node,flags,audioEffect)
{
	mBeganTouch=Touch::Zero;
}


TapGestureRecognizer::~TapGestureRecognizer(void)
{
	mNode=nullptr;
}

void TapGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.FirstValidActiveTouch();
			SetState(GestureState::Begin);
			if (mFlags.Has(GestureFlags::SuppressTouchBegan))
			{
				e.Handled=true;
			}
		}
		break;
	case GestureState::Begin:
		break;
	default:
		break;
	}

}

void TapGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		{
			if (!e.IsValid())
			{
				SetState(GestureState::Failed);
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
	switch(mState)
	{
	case GestureState::None:
		OnTapFailed(mNode);
		break;
	case GestureState::Begin:
		{
			if (e.IsValid()&&e.FindValidActiveTouchById(mBeganTouch.Id)!=nullptr)
			{
				if (!mFlags.Has(GestureFlags::SuppressAudio))
				{
					AudioEngine::Instance().PlayEffect(mAudioEffect.ToRef());
				}

				SetState(GestureState::Valid);
				TapGestureEventArg tapEventArg(this,e.FirstValidActiveTouch());
				OnTap(mNode,tapEventArg);
				SetState(GestureState::None);
				mBeganTouch=Touch::Zero;
				e.Handled=true;
				CancelOtherHandlers();

			}
		}
		break;
	default:
		break;
	}

	SetState(GestureState::None);
}

void TapGestureRecognizer::TryFireEvent( TouchEventArg& e )
{
	if (e.IsValid())
	{
		TapGestureEventArg tapEventArg(this,e.FirstValidActiveTouch());
		OnTap(mNode,tapEventArg);
		e.Handled=tapEventArg.Handled;
	}
}

void TapGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	SetState(GestureState::None);
}

bool TapGestureRecognizer::IsValid() const
{
	return mState==GestureState::Valid;
}

void TapGestureRecognizer::Reset()
{
	SetState(GestureState::None);
}



MEDUSA_END;