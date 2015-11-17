// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "BaseGestureEventArg.h"
#include "Node/Input/Touch.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class PanBeginGestureEventArg:public BaseGestureEventArg
{
public:
	PanBeginGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~PanBeginGestureEventArg(void){}
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void (INode* sender,PanBeginGestureEventArg&)> PanBeginDelegate;
typedef Event<void (INode* sender,PanBeginGestureEventArg&)> PanBeginEvent;

//[PRE_DECLARE_END]
MEDUSA_END;