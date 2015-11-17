// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING
#include "Core/Threading/ThreadPoolWork.h"
#include "Core/Threading/ThreadPool.h"

MEDUSA_BEGIN;
namespace ThreadingPrivate
{
	void NTAPI OnThreadpoolWorkCallback(PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext, PTP_WORK Work)
	{
		ICommand* command = (ICommand*)pvContext;
		RETURN_IF_NULL(command);
		command->Execute();
	}
}

ThreadPoolWork::ThreadPoolWork(const StringRef& name,ICommand* command)
	:mName(name),mCommand(command)
{
	SAFE_RETAIN(command);
	mWork = CreateThreadpoolWork(ThreadingPrivate::OnThreadpoolWorkCallback, command, &ThreadPool::Instance().mCallBackEnviron);

}

ThreadPoolWork::~ThreadPoolWork(void)
{
	SAFE_RELEASE(mCommand);

	if (mWork != nullptr)
	{
		CloseThreadpoolWork(mWork);
		mWork = nullptr;
	}
}

void ThreadPoolWork::Sumbit()
{
	SubmitThreadpoolWork(mWork);
}

void ThreadPoolWork::Wait(bool cancelPending /*= false*/)
{
	WaitForThreadpoolWorkCallbacks(mWork, cancelPending);
}

bool ThreadPoolWork::OnExecute()
{
	if (mCommand != nullptr)
	{
		mCommand->Execute();
	}

	return true;
}


MEDUSA_END;

#endif
