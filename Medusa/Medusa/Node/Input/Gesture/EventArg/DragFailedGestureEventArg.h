// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"

MEDUSA_BEGIN;

class DragFailedGestureEventArg:public BaseGestureEventArg
{
public:
	DragFailedGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~DragFailedGestureEventArg(void){}
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,DragFailedGestureEventArg&)> DragFailedDelegate;
typedef Event<void (INode* sender,DragFailedGestureEventArg&)> DragFailedEvent;

//[PRE_DECLARE_END]

MEDUSA_END;


