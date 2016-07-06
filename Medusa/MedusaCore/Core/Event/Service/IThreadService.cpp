// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IThreadService.h"

MEDUSA_BEGIN;

IThreadService::IThreadService(const StringRef& options /*= StringRef::Empty*/)
	:IService(options)
{
	mThread.SetCallback(Bind(&IThreadService::OnThread, this));
}


IThreadService::~IThreadService()
{
}


bool IThreadService::Start()
{
	switch (mState)
	{
	case ServiceState::None:
		mState = ServiceState::StartPending;
		mThread.Start();
		break;
	case ServiceState::StartPending:
		//keep waiting
		break;
	case ServiceState::Running:
		return true;
		break;
	case ServiceState::StopPending:
	default:
		return false;
	}
	return true;
}

bool IThreadService::Stop()
{
	switch (mState)
	{
	case ServiceState::Running:
	case ServiceState::StartPending:
		mState = ServiceState::StopPending;
		mThread.Join();
		break;
	case ServiceState::StopPending:
	case ServiceState::None:
		return true;
	default:
		return false;
	}

	return true;
}




void IThreadService::OnThread(Thread& thread)
{
	mState = ServiceState::Running;

	if (OnStart())
	{
		OnRun(thread);
	}
	
	mState = ServiceState::None;
	OnStop();
}

void IThreadService::OnRun(Thread& thread)
{
	while (!thread.IsCancelled())
	{
		BREAK_IF_FALSE(OnRunOnce(thread));
	}
}


MEDUSA_END;
