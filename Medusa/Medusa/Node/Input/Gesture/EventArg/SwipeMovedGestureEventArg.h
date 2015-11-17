// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Event.h"


MEDUSA_BEGIN;

class SwipeMovedGestureEventArg:public BaseGestureEventArg
{
public:
	SwipeMovedGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~SwipeMovedGestureEventArg(void){}
};


//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,SwipeMovedGestureEventArg&)> SwipeMovedDelegate;
typedef Event<void (INode* sender,SwipeMovedGestureEventArg&)> SwipeMovedEvent;

//[PRE_DECLARE_END]



MEDUSA_END;