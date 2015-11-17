// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;
struct IUpdatable
{
	virtual bool Update(float dt) { return true; }
	virtual ~IUpdatable() {}
};

MEDUSA_END;
