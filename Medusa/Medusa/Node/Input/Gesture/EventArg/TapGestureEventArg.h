// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Node/Input/Touch.h"
#include "Core/Pattern/Event.h"


MEDUSA_BEGIN;

class TapGestureEventArg:public BaseGestureEventArg
{
public:
	TapGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch):BaseGestureEventArg(recognizer),TouchInfo(touch){}
	virtual ~TapGestureEventArg(void){}
	Touch TouchInfo;
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,TapGestureEventArg&)> TapDelegate;
typedef Event<void (INode* sender,TapGestureEventArg&)> TapEvent;

typedef Delegate<void(INode* sender)> TapFailedDelegate;
typedef Event<void(INode* sender)> TapFailedEvent;


//[PRE_DECLARE_END]

MEDUSA_END;


