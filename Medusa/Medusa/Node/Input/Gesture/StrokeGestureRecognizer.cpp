// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/StrokeGestureRecognizer.h"
#include "Node/Input/Gesture/EventArg/StrokeGestureEventArg.h"

MEDUSA_BEGIN;

StrokeGestureRecognizer::StrokeGestureRecognizer(INode* node)
	:IGestureRecognizer(node)
{
}


StrokeGestureRecognizer::~StrokeGestureRecognizer(void)
{
	mNode = nullptr;
}

void StrokeGestureRecognizer::TouchesBegan(TouchEventArg& e)
{
	IInputHandler::TouchesBegan(e);
	switch (mState)
	{
	case InputState::None:
		if (e.IsOneFingerValid())
		{
			mStroke.Add(e.FirstValidActiveTouch().Pos);
			SetState(InputState::Begin);
			if (MEDUSA_FLAG_HAS(mBehaviors, InputBehaviors::SuppressTouchBegan))
			{
				e.Handled = true;
			}
		}
		break;
	case InputState::Begin:
		break;
	default:
		break;
	}

}

void StrokeGestureRecognizer::TouchesMoved(TouchEventArg& e)
{
	IInputHandler::TouchesMoved(e);
	switch (mState)
	{
	case InputState::None:
		break;
	case InputState::Begin:
	{
		if (e.IsOneFingerValid())
		{
			mStroke.Add(e.FirstValidActiveTouch().Pos);
		}
		else
		{
			SetState(InputState::Failed);
		}
	
	}
	break;
	default:
		break;
	}

}

void StrokeGestureRecognizer::TouchesEnded(TouchEventArg& e)
{
	IInputHandler::TouchesEnded(e);
	switch (mState)
	{
	case InputState::None:
		OnStrokeFailed(mNode);
		break;
	case InputState::Begin:
	{
		if (e.IsOneFingerValid())
		{
			mStroke.Add(e.FirstValidActiveTouch().Pos);
			SetState(InputState::Valid);

			//recognize
			StrokeGestureEventArg strokeEventArg(this,nullptr);
			RaiseEvent(InputEventType::Stroke, &strokeEventArg);

			SetState(InputState::None);
			e.Handled = true;
			CancelOtherHandlers();
		}
	
	}
	break;
	default:
		break;
	}

	SetState(InputState::None);
}


void StrokeGestureRecognizer::TouchesCancelled(TouchEventArg& e)
{
	IInputHandler::TouchesCancelled(e);
	SetState(InputState::None);
	mStroke.Clear();
}

bool StrokeGestureRecognizer::IsValid() const
{
	return mState == InputState::Valid;
}

void StrokeGestureRecognizer::Reset()
{
	SetState(InputState::None);
}



MEDUSA_END;