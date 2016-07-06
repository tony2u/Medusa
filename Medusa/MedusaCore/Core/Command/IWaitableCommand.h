// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Command/ICommand.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Threading/IWaitable.h"

MEDUSA_BEGIN;


class IWaitableCommand :public ICommand,public IWaitable
{
	MEDUSA_RTTI(IWaitableCommand,ICommand);
public:
	IWaitableCommand();
	virtual ~IWaitableCommand(void);
	bool IsCompleted() const { return mCompleteEvent.IsSet(); }

	virtual bool OnExit()override;

	virtual bool Wait()override;
protected:
	ThreadEvent mCompleteEvent;
};

MEDUSA_END;
