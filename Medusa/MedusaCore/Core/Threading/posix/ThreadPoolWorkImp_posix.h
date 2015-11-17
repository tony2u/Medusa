// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadEvent.h"

MEDUSA_BEGIN;


class ThreadPoolWorkImp
{
public:
	ThreadPoolWorkImp();
	~ThreadPoolWorkImp(void);
protected:
	ThreadEvent mCompleteEvent;
};

MEDUSA_END;
#endif