// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/DragGestureRecognizer.h"
#include "Node/Input/EventArg/TouchEventArg.h"

MEDUSA_BEGIN;
DragGestureRecognizer::DragGestureRecognizer( INode* node, float minDistance,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags)
{
	Reset();
	mMinDistance = minDistance;
	mBeganTouch=Touch::Zero;
}


DragGestureRecognizer::~DragGestureRecognizer(void)
{
	mNode = nullptr;
}

void DragGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsValid())
		{
			mBeganTouch=e.FirstValidActiveTouch();
            SetState(GestureState::Begin);
			DragBeganGestureEventArg dragBeganGestureEventArg(this,mBeganTouch);
			OnDragBegan(mNode,dragBeganGestureEventArg);
			e.Handled=dragBeganGestureEventArg.Handled;
		}
		break;
	default:
		break;
	}
    
}

void DragGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
        {
			Touch* nextTouch=e.FindValidActiveTouchById(mBeganTouch.Id);
			if (nextTouch!=nullptr)
			{
				Point2F movement = nextTouch->Pos-mBeganTouch.Pos;
				if (movement.Length() > mMinDistance)
				{
					// Valid
					SetState(GestureState::Valid);

					DragingGestureEventArg dragingGestureEventArg(this,*nextTouch,movement);
					OnDraging(mNode,dragingGestureEventArg);
					e.Handled=true;
					CancelOtherHandlers();

				}
				else
				{
					// Recognizing
					SetState(GestureState::Recognizing);
				}

			}
           
        }
        break;
	case GestureState::Valid:
		{
			Touch* validTouch=e.FindValidActiveTouchById(mBeganTouch.Id);
			if (validTouch!=nullptr)
			{
				Point2F movement = validTouch->Pos-mBeganTouch.Pos;
				DragingGestureEventArg dragingGestureEventArg(this,*validTouch,movement);
				OnDraging(mNode,dragingGestureEventArg);
				e.Handled=true;
				CancelOtherHandlers();

			}
		}
		break;
	default:
		break;
	}
}

void DragGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		{
			SetState(GestureState::Failed);
			DragFailedGestureEventArg dragFailedGestureEventArg(this);
			OnDragFailed(mNode,dragFailedGestureEventArg);
            Reset();
		}
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
	case GestureState::Valid:
		{
			Touch* validTouch=e.FindValidActiveTouchById(mBeganTouch.Id);
			if (validTouch!=nullptr)
			{
				//Point2F movement = validTouch->Pos-mBeganTouch.Pos;
				DragEndGestureEventArg dragEndGestureEventArg(this,*validTouch);
				OnDragEnd(mNode,dragEndGestureEventArg);
				e.Handled=true;
			}
		}
		break;
	default:
		break;
	}

}

void DragGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	Reset();
}

bool DragGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case GestureState::Valid:
		return true;
	default:
		return false;
	}
}

void DragGestureRecognizer::Reset()
{
	SetState( GestureState::None);
	mBeganTouch=Touch::Zero;
}


MEDUSA_END;