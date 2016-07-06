// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Command/ICommand.h"

MEDUSA_BEGIN;


class SleepCommand :public ICommand
{
	MEDUSA_RTTI(SleepCommand,ICommand);

public:
	SleepCommand(long milliseconds = 0);
	virtual ~SleepCommand(void);

	virtual bool OnExecute()override;
protected:
	long mMilliseconds;
};

MEDUSA_END;
