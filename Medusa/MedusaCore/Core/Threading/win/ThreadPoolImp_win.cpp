// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING
#include "ThreadPoolImp_win.h"
#include "Core/System/Environment.h"

MEDUSA_BEGIN;

ThreadPoolImp::ThreadPoolImp()
{
	mPool = nullptr;
	mCleanGroup = nullptr;
}

ThreadPoolImp::~ThreadPoolImp(void)
{

}
bool ThreadPoolImp::InitializeHelper(uint minCount /*= ThreadPoolImp::MinCount*/, uint maxCount /*= ThreadPoolImp::MaxCount*/, bool autoManaged /*= true*/)
{
	RETURN_TRUE_IF_NOT_NULL(mPool);

	mPool = CreateThreadpool(nullptr);
	RETURN_FALSE_IF_NULL(mPool);

	//default is 0-1500
	if (autoManaged)
	{
		uint cpuCount = Environment::Instance().GetCPUCount();
		minCount = 2;
		maxCount = cpuCount * 2 + 2;
	}

	SetThreadpoolThreadMaximum(mPool, maxCount);
	if (SetThreadpoolThreadMinimum(mPool, minCount) == FALSE)
	{
		UninitialzieHelper();
		return false;
	}
	InitializeThreadpoolEnvironment(&mCallBackEnviron);
	SetThreadpoolCallbackPool(&mCallBackEnviron, mPool);

	mCleanGroup = CreateThreadpoolCleanupGroup();
	if (mCleanGroup == nullptr)
	{
		UninitialzieHelper();
		return false;
	}

	SetThreadpoolCallbackCleanupGroup(&mCallBackEnviron, mCleanGroup, nullptr);

	return true;
}

void ThreadPoolImp::UninitialzieHelper()
{
	if (mCleanGroup != nullptr)
	{
		CloseThreadpoolCleanupGroupMembers(mCleanGroup, FALSE, nullptr);
		CloseThreadpoolCleanupGroup(mCleanGroup);
		mCleanGroup = nullptr;
	}


	if (mPool != nullptr)
	{
		DestroyThreadpoolEnvironment(&mCallBackEnviron);
		CloseThreadpool(mPool);
		mPool = nullptr;
	}
}




MEDUSA_END;

#endif
