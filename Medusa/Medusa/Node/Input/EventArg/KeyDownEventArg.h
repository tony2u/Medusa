// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseKeyEventArg.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class KeyDownEventArg:public BaseKeyEventArg
{
	MEDUSA_RTTI(KeyDownEventArg,BaseKeyEventArg);
public:
	KeyDownEventArg(uint keyData,uint status);
	virtual ~KeyDownEventArg(void){}
	
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void(INode* sender, KeyDownEventArg&)> KeyDownDelegate;
typedef Event<void(INode* sender, KeyDownEventArg&)> KeyDownEvent;
//[PRE_DECLARE_END]

MEDUSA_END;