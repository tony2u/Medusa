// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Node/Input/Touch.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class PinchGestureEventArg:public BaseGestureEventArg
{
public:
	PinchGestureEventArg(IGestureRecognizer* recognizer,float scaleFactor,Point2F middlePoint):BaseGestureEventArg(recognizer),ScaleFactor(scaleFactor),MiddlePoint(middlePoint){}
	virtual ~PinchGestureEventArg(void){}
	float ScaleFactor;
	Point2F MiddlePoint;
};
//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,PinchGestureEventArg&)> PinchDelegate;
typedef Event<void (INode* sender,PinchGestureEventArg&)> PinchEvent;

//[PRE_DECLARE_END]



MEDUSA_END;