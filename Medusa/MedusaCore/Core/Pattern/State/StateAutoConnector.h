// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IStateConnector.h"

MEDUSA_BEGIN;

class StateAutoConnector :public IStateConnector
{
public:
	StateAutoConnector();
	virtual ~StateAutoConnector(void);
};

MEDUSA_END;
