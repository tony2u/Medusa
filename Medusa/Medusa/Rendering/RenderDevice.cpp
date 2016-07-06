// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderDevice.h"

MEDUSA_BEGIN;

RenderDevice::RenderDevice()
{
	mCurrentThreadId = 0;
}

RenderDevice::~RenderDevice(void)
{

}

bool RenderDevice::Initialize(bool disableThreading /*= false*/)
{
	bool result = TFrameCommandExecutor::Initialize(disableThreading);
	if (!disableThreading)
	{
		mCurrentThreadId = Id();
	}
	else
	{
		mCurrentThreadId = Thread::CurrentId();
	}
	return result;
}

bool RenderDevice::Uninitialize()
{
	return TFrameCommandExecutor::Uninitialize();
}

bool RenderDevice::NeedAsync() const
{
	return !Thread::IsCurrent(mCurrentThreadId);
}

MEDUSA_END;