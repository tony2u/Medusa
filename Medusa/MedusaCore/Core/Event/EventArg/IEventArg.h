// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;

class IEventArg :public RTTIObject
{
	MEDUSA_RTTI_ROOT(IEventArg);
public:
	IEventArg() = default;
	virtual ~IEventArg(void) = default;
public:
	static IEventArg Empty;
	volatile bool Handled = false;
};



MEDUSA_END;