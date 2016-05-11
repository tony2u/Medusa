// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/INode.h"
#include "Geometry/Matrix4.h"
#include "Core/Log/Log.h"
#include "Graphics/ResolutionAdapter.h"
#include "Resource/Camera/Camera.h"


MEDUSA_BEGIN;
TouchEventArg::~TouchEventArg(void)
{
}


void TouchEventArg::UpdateValidActiveTouches( INode* node )
{
	mLocalActiveTouches.Clear();
	mValidActiveTouches.Clear();

	FOR_EACH_COLLECTION(i, mWorldActiveTouches)
	{
		Touch& touch = *i;
		Point2F pos = node->TransformToLocal(touch.Pos);
		Touch localTouch = touch;
		localTouch.Pos = pos;
		mLocalActiveTouches.Add(localTouch);
		if (node->HitTestLocal(pos))
		{
			mValidActiveTouches.Add(localTouch);
		}
	}
}


void TouchEventArg::UpdateValidCurrentTouches(INode* node)
{
	mLocalCurrentTouches.Clear();
	mValidCurrentTouches.Clear();
	FOR_EACH_COLLECTION(i, mWorldCurrentTouches)
	{
		Touch& touch = *i;
		Point2F pos = node->TransformToLocal(touch.Pos);
		Touch localTouch = touch;
		localTouch.Pos = pos;
		mLocalCurrentTouches.Add(localTouch);
		if (node->HitTestLocal(pos))
		{
			mValidCurrentTouches.Add(localTouch);
		}
	}
}

bool TouchEventArg::IsTouchValid( INode* node,Point2F pos ) const
{
	return node->HitTestWorld(pos);
}

Point2F TouchEventArg::GetValidActiveMiddlePoint() const
{
	size_t count=mValidActiveTouches.Count();
	switch(count)
	{
	case 0:
		return Point2F::Zero;
	case 1:
		return mValidActiveTouches[0].Pos;
	default:
		{
			Point2F result=Point2F::Zero;
			FOR_EACH_COLLECTION(i,mValidActiveTouches)
			{
				result+=(*i).Pos;
			}

			result/=count;

			return result;
		}
	}


	
}

Point2F TouchEventArg::GetActiveMiddlePoint() const
{
	size_t count = mWorldActiveTouches.Count();
	switch(count)
	{
	case 0:
		return Point2F::Zero;
	case 1:
		return mWorldActiveTouches[0].Pos;;
	default:
		{
			Point2F result;
			FOR_EACH_COLLECTION(i,mWorldActiveTouches)
			{
				result+=(*i).Pos;
			}
			result/=count;

			return result;
		}
	}

	

}


const Touch* TouchEventArg::FindWorldActiveTouchById(intp id) const
{
	FOR_EACH_COLLECTION(i,mWorldActiveTouches)
	{
		const Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return nullptr;
}

const Touch* TouchEventArg::FindLocalActiveTouchById(intp id) const
{
	FOR_EACH_COLLECTION(i,mLocalActiveTouches)
	{
		const Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return nullptr;
}

const Touch* TouchEventArg::FindValidActiveTouchById(intp id) const
{
	FOR_EACH_COLLECTION(i,mValidActiveTouches)
	{
		const Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return nullptr;
}

Touch* TouchEventArg::FindValidActiveTouchById(intp id)
{
	FOR_EACH_COLLECTION(i,mValidActiveTouches)
	{
		Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return nullptr;
}
void TouchEventArg::MergeValidActiveTouches(const TouchEventArg& e)
{
	const List<Touch>& touches=e.ValidActiveTouches();
	FOR_EACH_COLLECTION(i,touches)
	{
		const Touch& touch=*i;
		Touch* originalTouch=FindValidActiveTouchById(touch.Id);
		if (originalTouch==nullptr)
		{
			AddValidActiveTouch(touch);
		}
		else
		{
			*originalTouch=touch;
		}
	}
}

void TouchEventArg::MoveValidActiveTouches(const TouchEventArg& e)
{
	const List<Touch>& touches=e.ValidActiveTouches();
	FOR_EACH_COLLECTION(i,touches)
	{
		const Touch& touch=*i;
		Touch* originalTouch=FindValidActiveTouchById(touch.Id);
		if (originalTouch!=nullptr)
		{
			*originalTouch=touch;
		}
	}
}

void TouchEventArg::RemoveValidActiveTouches(const TouchEventArg& e)
{
	const List<Touch>& touches=e.WorldActiveTouches();	//remove all even move out of view
	FOR_EACH_COLLECTION(i,touches)
	{
		const Touch& touch=*i;
		Touch* originalTouch=FindValidActiveTouchById(touch.Id);
		if (originalTouch!=nullptr)
		{
			mValidActiveTouches.Remove(touch);
		}
	}
}


void TouchEventArg::PrintDebugString()
{
	FOR_EACH_COLLECTION(i,mWorldActiveTouches)
	{
		const Touch& touch=*i;
		Log::FormatInfo("WorldTouch:{} ({},{})",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
	FOR_EACH_COLLECTION(i,mLocalActiveTouches)
	{
		const Touch& touch=*i;
		Log::FormatInfo("LocalTouch:{} ({},{})",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
	FOR_EACH_COLLECTION(i,mValidActiveTouches)
	{
		const Touch& touch=*i;
		Log::FormatInfo("ValidTouch:{} ({},{})",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
}

void TouchEventArg::Clear()
{
	mWorldActiveTouches.Clear();
	mLocalActiveTouches.Clear();
	mValidActiveTouches.Clear();
}

bool TouchEventArg::IsAllTouchEnded() const
{
	if (mPhase==TouchPhase::Ended||mPhase==TouchPhase::Cancelled)
	{
		return mWorldCurrentTouches.Count()-mWorldActiveTouches.Count()==0;
	}
	return false;
}

MEDUSA_END;