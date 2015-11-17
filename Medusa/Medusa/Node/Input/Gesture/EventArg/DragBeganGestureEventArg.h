// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Node/Input/Touch.h"

MEDUSA_BEGIN;


class DragBeganGestureEventArg:public BaseGestureEventArg
{
public:
	DragBeganGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch):BaseGestureEventArg(recognizer),TouchInfo(touch){}
	virtual ~DragBeganGestureEventArg(void){}
	Touch TouchInfo;
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,DragBeganGestureEventArg&)> DragBeganDelegate;
typedef Event<void (INode* sender,DragBeganGestureEventArg&)> DragBeganEvent;

//[PRE_DECLARE_END]


MEDUSA_END;


