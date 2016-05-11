// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "BaseMainCommandProcessor.h"
#include "Core/Threading/Mutex.h"
#include "Core/Threading/ScopedLock.h"

MEDUSA_BEGIN;

class MainCommandProcessor :public Singleton < MainCommandProcessor >,public BaseMainCommandProcessor<ScopedLock>
{
	friend class Singleton < MainCommandProcessor > ;
	MainCommandProcessor(void) = default;
	virtual ~MainCommandProcessor(void) = default;
public:
	
};


MEDUSA_END;