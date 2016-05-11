// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;

class IEventArg:public RTTIObject
{
	MEDUSA_DECLARE_RTTI_ROOT;
public:
	IEventArg():Handled(false){}
	virtual ~IEventArg(void){}
public:
	static IEventArg Empty;
	volatile bool Handled;
};



MEDUSA_END;