// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Event.h"


MEDUSA_BEGIN;

class SwipeBeginGestureEventArg:public BaseGestureEventArg
{
public:
	SwipeBeginGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~SwipeBeginGestureEventArg(void){}
};


//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,SwipeBeginGestureEventArg&)> SwipeBeginDelegate;
typedef Event<void (INode* sender,SwipeBeginGestureEventArg&)> SwipeBeginEvent;

//[PRE_DECLARE_END]



MEDUSA_END;