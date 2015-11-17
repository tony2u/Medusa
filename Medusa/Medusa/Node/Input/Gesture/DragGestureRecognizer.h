// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"
#include "Node/Input/Gesture/EventArg/DragBeganGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DragingGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DragEndGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DragFailedGestureEventArg.h"
MEDUSA_BEGIN;


class DragGestureRecognizer: public IGestureRecognizer
{
    
public:
	DragGestureRecognizer(INode* node, float delta,GestureFlags flags=GestureFlags::None);
	virtual ~DragGestureRecognizer(void);
	virtual InputType GetInputType() const{ return InputType::Drag; }

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);

	virtual bool IsValid()const;
	virtual void Reset();

	virtual bool HasHandler()const{return !OnDragBegan.IsEmpty()||!OnDraging.IsEmpty()||!OnDragEnd.IsEmpty()||!OnDragFailed.IsEmpty();}

	DragBeganEvent OnDragBegan;
	DragingEvent OnDraging;
	DragEndEvent OnDragEnd;
	DragFailedEvent OnDragFailed;

private:
	float mMinDistance;
	Touch mBeganTouch;
};



MEDUSA_END;