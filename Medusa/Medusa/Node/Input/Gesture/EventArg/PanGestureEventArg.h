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

class PanGestureEventArg:public BaseGestureEventArg
{
public:
	PanGestureEventArg(IGestureRecognizer* recognizer,const Point2F& movement):BaseGestureEventArg(recognizer),Movement(movement){}
	virtual ~PanGestureEventArg(void){}
	Point2F Movement;
};
//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,PanGestureEventArg&)> PanDelegate;
typedef Event<void (INode* sender,PanGestureEventArg&)> PanEvent;

//[PRE_DECLARE_END]



MEDUSA_END;