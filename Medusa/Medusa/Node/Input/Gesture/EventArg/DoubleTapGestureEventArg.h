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

class DoubleTapGestureEventArg:public BaseGestureEventArg
{
public:
	DoubleTapGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch,float duration):BaseGestureEventArg(recognizer),TouchInfo(touch),Duration(duration){}
	virtual ~DoubleTapGestureEventArg(void){}
	Touch TouchInfo;
	float Duration;
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,DoubleTapGestureEventArg&)> DoubleTapDelegate;
typedef Event<void (INode* sender,DoubleTapGestureEventArg&)> DoubleTapEvent;

//[PRE_DECLARE_END]

MEDUSA_END;