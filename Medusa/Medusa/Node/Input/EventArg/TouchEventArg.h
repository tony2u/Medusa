// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"
#include "Geometry/Point2.h"
#include "Node/Input/Touch.h"
#include "Core/Command/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class TouchEventArg:public IEventArg
{
public:
	TouchEventArg(TouchPhase eventType,const List<Touch>& touches,const List<Touch>& currentTouches=List<Touch>::Empty)
		:mPhase(eventType),mWorldActiveTouches(touches),mWorldCurrentTouches(currentTouches)
	{
		if (mWorldCurrentTouches.IsEmpty())
		{
			mWorldCurrentTouches=touches;
		}
	}

	TouchEventArg(TouchPhase eventType,const Touch& touch,const List<Touch>& currentTouches=List<Touch>::Empty)
		:mPhase(eventType),mWorldCurrentTouches(currentTouches)
	{
		mWorldActiveTouches.Add(touch);
		if (mWorldCurrentTouches.IsEmpty())
		{
			mWorldCurrentTouches.Add(touch);
		}
	}

	TouchEventArg()
		:mPhase(TouchPhase::Began)
	{

	}

	TouchEventArg(TouchPhase phase) 
		:mPhase(phase)
	{

	}

	
	virtual ~TouchEventArg(void);
	TouchPhase Phase() const { return mPhase; }
	void AddActiveTouch(const Touch& touch){mWorldActiveTouches.Add(touch);}
	void UpdateValidActiveTouches(INode* node);
	void UpdateValidCurrentTouches(INode* node);


	const List<Touch>& WorldActiveTouches()const { return mWorldActiveTouches; }
	bool IsOneFinger()const{return mWorldActiveTouches.Count()==1;}
	bool IsTwoFinger()const{return mWorldActiveTouches.Count()==2;}
	bool IsMultipleTouching()const{return mWorldActiveTouches.Count()>=2;}
	const Touch& FirstWorldActiveTouch()const{return mWorldActiveTouches.First();}
	size_t WorldActiveTouchCount()const{return mWorldActiveTouches.Count();}


	const List<Touch>& LocalActiveTouches()const{ return mLocalActiveTouches; }
	const Touch& FirstLocalActiveTouch()const{return mLocalActiveTouches.First();}
	size_t LocalActiveTouchCount()const{return mLocalActiveTouches.Count();}


	void AddValidActiveTouch(const Touch& touch){mValidActiveTouches.Add(touch);}

	void MergeValidActiveTouches(const TouchEventArg& e);
	void MoveValidActiveTouches(const TouchEventArg& e);
	void RemoveValidActiveTouches(const TouchEventArg& e);


	const List<Touch>& ValidActiveTouches()const  { return mValidActiveTouches; }
	bool IsValid()const{return !mValidActiveTouches.IsEmpty();}
	bool IsOneFingerValid()const{return mValidActiveTouches.Count()==1;}
	bool IsTwoFingerValid()const{return mValidActiveTouches.Count()==2;}
	const Touch& FirstValidActiveTouch()const{return mValidActiveTouches.First();}
	size_t ValidTouchActiveCount()const{return mValidActiveTouches.Count();}

	Point2F GetValidActiveMiddlePoint()const;
	Point2F GetActiveMiddlePoint()const;

	const Touch* FindWorldActiveTouchById(intp id)const;
	const Touch* FindLocalActiveTouchById(intp id)const;
	const Touch* FindValidActiveTouchById(intp id)const;
	Touch* FindValidActiveTouchById(intp id);
	void PrintDebugString();

	void Clear();

	//////////////////////////////////////////////////////////////////////////
	const List<Touch>& WorldCurrentTouches()const { return mWorldCurrentTouches; }

	List<Touch>& MutableWorldCurrentTouches() { return mWorldCurrentTouches; }
	List<Touch>& MutableWorldActiveTouches() { return mWorldActiveTouches; }

	bool IsAllTouchEnded()const;
protected:
	bool IsTouchValid(INode* node,Point2F pos)const;

protected:
	TouchPhase mPhase;

	//active
	List<Touch> mWorldActiveTouches;
	List<Touch> mLocalActiveTouches;
	List<Touch> mValidActiveTouches;
	//current
	List<Touch> mWorldCurrentTouches;
	List<Touch> mLocalCurrentTouches;
	List<Touch> mValidCurrentTouches;

};


MEDUSA_END;