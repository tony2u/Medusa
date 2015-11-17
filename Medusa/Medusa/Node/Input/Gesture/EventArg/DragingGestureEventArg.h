// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Node/Input/Touch.h"

MEDUSA_BEGIN;

class DragingGestureEventArg:public BaseGestureEventArg
{
public:
	DragingGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch,Point2F movement):BaseGestureEventArg(recognizer),TouchInfo(touch),Movement(movement){}
	virtual ~DragingGestureEventArg(void){}
	Touch TouchInfo;
	Point2F Movement;
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,DragingGestureEventArg&)> DragingDelegate;
typedef Event<void (INode* sender,DragingGestureEventArg&)> DragingEvent;

//[PRE_DECLARE_END]

MEDUSA_END;


