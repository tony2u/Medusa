// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifndef MEDUSA_POSIX_THREADING

#include "Core/Threading/ThreadingDefines.h"

MEDUSA_BEGIN;


class ThreadPoolImp
{
public:
	ThreadPoolImp();
	~ThreadPoolImp(void);
public:
	const static uint MinCount = 2;
	const static uint MaxCount = 8;
protected:
	bool InitializeHelper(uint minCount = ThreadPoolImp::MinCount, uint maxCount = ThreadPoolImp::MaxCount, bool autoManaged = true);
	void UninitialzieHelper();
protected:
	PTP_POOL mPool;
	PTP_CLEANUP_GROUP mCleanGroup;
	TP_CALLBACK_ENVIRON mCallBackEnviron;
};


MEDUSA_END;
#endif