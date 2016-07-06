// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseGestureEventArg.h"
#include "Core/Pattern/Event.h"


MEDUSA_BEGIN;

class StrokeGestureEventArg :public BaseGestureEventArg
{
public:
	StrokeGestureEventArg(IGestureRecognizer* recognizer, SingleStrokeTemplate* val) :BaseGestureEventArg(recognizer), Result(val) {}
	virtual ~StrokeGestureEventArg(void) {}
	SingleStrokeTemplate* Result;
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void(INode* sender, StrokeGestureEventArg&)> StrokeDelegate;
typedef Event<void(INode* sender, StrokeGestureEventArg&)> StrokeEvent;

typedef Delegate<void(INode* sender)> StrokeFailedDelegate;
typedef Event<void(INode* sender)> StrokeFailedEvent;

//[PRE_DECLARE_END]

MEDUSA_END;


