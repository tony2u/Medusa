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

	for (auto& touch : mWorldActiveTouches)
	{
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
	for (auto& touch : mWorldCurrentTouches)
	{
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
			for( auto i:mValidActiveTouches)
			{
				result+=i.Pos;
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
			for(auto i:mWorldActiveTouches)
			{
				result+=i.Pos;
			}
			result/=count;

			return result;
		}
	}

	

}


const Touch* TouchEventArg::FindWorldActiveTouchById(intp id) const
{
	for (auto& touch : mWorldActiveTouches)
	{
		
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return nullptr;
}

const Touch* TouchEventArg::FindLocalActiveTouchById(intp id) const
{
	for (auto& touch : mLocalActiveTouches)
	{
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return nullptr;
}

const Touch* TouchEventArg::FindValidActiveTouchById(intp id) const
{
	for (auto& touch : mValidActiveTouches)
	{
		
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return nullptr;
}

Touch* TouchEventArg::FindValidActiveTouchById(intp id)
{
	for (auto& touch : mValidActiveTouches)
	{
		
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
	for (auto& touch : touches)
	{
		
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
	for (auto& touch : touches)
	{
		
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
	for (auto& touch : touches)
	{
		Touch* originalTouch=FindValidActiveTouchById(touch.Id);
		if (originalTouch!=nullptr)
		{
			mValidActiveTouches.Remove(touch);
		}
	}
}


void TouchEventArg::PrintDebugString()
{
	for (auto& touch : mWorldActiveTouches)
	{
		Log::FormatInfo("WorldTouch:{} ({},{})",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
	for (auto& touch : mLocalActiveTouches)
	{
		Log::FormatInfo("LocalTouch:{} ({},{})",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
	for (auto& touch : mValidActiveTouches)
	{
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