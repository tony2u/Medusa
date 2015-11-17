// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Command/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class BaseGestureEventArg:public IEventArg
{
public:
	BaseGestureEventArg(IGestureRecognizer* recognizer):Recognizer(recognizer){}
	virtual ~BaseGestureEventArg(void){}
	IGestureRecognizer* Recognizer;
};

MEDUSA_END;