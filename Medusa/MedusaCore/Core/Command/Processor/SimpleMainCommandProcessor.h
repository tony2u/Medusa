// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "BaseMainCommandProcessor.h"
#include "Core/Threading/ScopedNoLock.h"

MEDUSA_BEGIN;

class SimpleMainCommandProcessor :public BaseMainCommandProcessor<ScopedNoLock>
{
public:
	using BaseMainCommandProcessor<ScopedNoLock>::Receive;
	using BaseMainCommandProcessor<ScopedNoLock>::ReceiveAsync;
	using BaseMainCommandProcessor<ScopedNoLock>::WaitForComplete;
	using BaseMainCommandProcessor<ScopedNoLock>::Clear;
	using BaseMainCommandProcessor<ScopedNoLock>::ClearWithoutRun;


	SimpleMainCommandProcessor(void) = default;
	virtual ~SimpleMainCommandProcessor(void) = default;
	
};


MEDUSA_END;