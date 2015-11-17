// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/EventArg/BaseKeyEventArg.h"
MEDUSA_BEGIN;

BaseKeyEventArg::BaseKeyEventArg(uint keyData,uint status) 
{
	mKeyData=(Keys)keyData;
	mStatus=status;
}


MEDUSA_IMPLEMENT_RTTI(BaseKeyEventArg,IEventArg);
MEDUSA_END;