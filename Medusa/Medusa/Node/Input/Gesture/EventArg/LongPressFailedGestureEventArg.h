// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"

MEDUSA_BEGIN;

class LongPressFailedGestureEventArg:public BaseGestureEventArg
{
public:
	LongPressFailedGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~LongPressFailedGestureEventArg(void){}
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,LongPressFailedGestureEventArg&)> LongPressFailedDelegate;
typedef Event<void (INode* sender,LongPressFailedGestureEventArg&)> LongPressFailedEvent;

//[PRE_DECLARE_END]

MEDUSA_END;


