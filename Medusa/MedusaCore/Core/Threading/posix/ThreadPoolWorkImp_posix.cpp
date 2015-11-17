// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_POSIX_THREADING

#include "Core/Threading/posix/ThreadPoolWorkImp_posix.h"

MEDUSA_BEGIN;

ThreadPoolWorkImp::ThreadPoolWorkImp()
	:mCompleteEvent(false,true)
{
	
}

ThreadPoolWorkImp::~ThreadPoolWorkImp(void)
{
	
}

MEDUSA_END;

#endif