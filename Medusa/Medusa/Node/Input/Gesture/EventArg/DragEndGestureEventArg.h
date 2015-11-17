// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Node/Input/Touch.h"

MEDUSA_BEGIN;

class DragEndGestureEventArg:public BaseGestureEventArg
{
public:
	DragEndGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch):BaseGestureEventArg(recognizer),TouchInfo(touch){}
	virtual ~DragEndGestureEventArg(void){}
	Touch TouchInfo;
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,DragEndGestureEventArg&)> DragEndDelegate;
typedef Event<void (INode* sender,DragEndGestureEventArg&)> DragEndEvent;

//[PRE_DECLARE_END]

MEDUSA_END;


