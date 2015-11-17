// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifndef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadingDefines.h"

MEDUSA_BEGIN;


class ThreadPoolWorkImp
{
public:
	ThreadPoolWorkImp();
	~ThreadPoolWorkImp(void);
protected:
	PTP_WORK mWork;
};

MEDUSA_END;
#endif