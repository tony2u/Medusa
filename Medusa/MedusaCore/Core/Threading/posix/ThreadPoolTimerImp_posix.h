// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadEvent.h"
#include "Core/Profile/StopWatch.h"

MEDUSA_BEGIN;


class ThreadPoolTimerImp
{
public:
	ThreadPoolTimerImp();
	~ThreadPoolTimerImp(void);
protected:
	ThreadEvent mCompleteEvent;
	StopWatch mWatch;
	bool mIsSubmitted;
	volatile bool mIsCancelled;
};

MEDUSA_END;
#endif