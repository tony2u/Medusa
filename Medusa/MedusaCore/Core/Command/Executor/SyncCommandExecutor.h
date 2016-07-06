// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "TSyncCommandExecutor.h"
#include "Core/Threading/Mutex.h"
#include "Core/Threading/ScopedLock.h"

MEDUSA_BEGIN;

class SyncCommandExecutor :public Singleton < SyncCommandExecutor >,public TSyncCommandExecutor<ICommand,ScopedLock>
{
	friend class Singleton < SyncCommandExecutor > ;
	SyncCommandExecutor(void) = default;
	virtual ~SyncCommandExecutor(void) = default;
public:
	
};


MEDUSA_END;