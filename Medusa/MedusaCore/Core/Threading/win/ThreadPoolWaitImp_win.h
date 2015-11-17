// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifndef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadingDefines.h"

MEDUSA_BEGIN;


class ThreadPoolWaitImp
{
public:
	ThreadPoolWaitImp();
	~ThreadPoolWaitImp(void);
protected:
	PTP_WAIT mWait;
};

MEDUSA_END;
#endif