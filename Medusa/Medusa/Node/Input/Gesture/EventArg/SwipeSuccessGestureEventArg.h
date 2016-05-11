// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Event.h"
#include "Geometry/ScrollDirection.h"

MEDUSA_BEGIN;

class SwipeSuccessGestureEventArg:public BaseGestureEventArg
{
public:
	SwipeSuccessGestureEventArg(IGestureRecognizer* recognizer, ScrollDirection directionSucceed) :BaseGestureEventArg(recognizer), DirectionSucceed(directionSucceed) {}
	virtual ~SwipeSuccessGestureEventArg(void){}
	ScrollDirection DirectionSucceed;
};


//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,SwipeSuccessGestureEventArg&)> SwipeSuccessDelegate;
typedef Event<void (INode* sender,SwipeSuccessGestureEventArg&)> SwipeSuccessEvent;

//[PRE_DECLARE_END]



MEDUSA_END;