// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseKeyEventArg.h"
#include "Core/Pattern/Event.h"



MEDUSA_BEGIN;

class CharInputEventArg :public BaseKeyEventArg
{
	MEDUSA_DECLARE_RTTI;

public:
	CharInputEventArg(uint key, uint status);
	virtual ~CharInputEventArg(void){}
	wchar_t Char()const{ return (wchar_t)KeyCode(); }
};


//[PRE_DECLARE_BEGIN]
typedef Delegate<void(INode* sender, CharInputEventArg&)> CharInputDelegate;
typedef Event<void(INode* sender, CharInputEventArg&)> CharInputEvent;
//[PRE_DECLARE_END]


MEDUSA_END;