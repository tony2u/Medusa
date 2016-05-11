// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"


MEDUSA_BEGIN;

class LongPressGestureRecognizer:public IGestureRecognizer
{
	
public:
	typedef Delegate<void (INode* sender,LongPressBeganGestureEventArg&)> LongPressBeganEventHandler;
	typedef Delegate<void (INode* sender,LongPressFailedGestureEventArg&)> LongPressFailedEventHandler;

	LongPressGestureRecognizer(INode* node,float minPressDuration,float allowMovement);
	virtual ~LongPressGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::LongPress;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual bool Update(float dt);
	virtual void Reset();
	virtual bool IsValid()const;
	virtual bool HasHandler()const{return !OnLongPressBegan.IsEmpty()||!OnLongPressFailed.IsEmpty();}
	virtual bool NeedUpdate()const { return true; }

	LongPressBeganEvent OnLongPressBegan;
	LongPressFailedEvent OnLongPressFailed;


private:
	float mMinPressDuration;
	float mAllowMovement;

	Touch mBeganTouch;
	float mBeginTimeStamp;
};



MEDUSA_END;