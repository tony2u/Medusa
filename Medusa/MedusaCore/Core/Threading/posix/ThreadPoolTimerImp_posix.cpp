// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING

#include "Core/Threading/posix/ThreadPoolTimerImp_posix.h"

MEDUSA_BEGIN;

ThreadPoolTimerImp::ThreadPoolTimerImp()
	:mCompleteEvent(false,true)
{
	
}

ThreadPoolTimerImp::~ThreadPoolTimerImp(void)
{
	
}

MEDUSA_END;

#endif