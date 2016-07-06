// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseKeyEventArg.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class KeyUpEventArg:public BaseKeyEventArg
{
	MEDUSA_RTTI(KeyUpEventArg,BaseKeyEventArg);
public:
	KeyUpEventArg(uint keyData,uint status);
	virtual ~KeyUpEventArg(void){}
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void(INode* sender, KeyUpEventArg&)> KeyUpDelegate;
typedef Event<void(INode* sender, KeyUpEventArg&)> KeyUpEvent;
//[PRE_DECLARE_END]

MEDUSA_END;