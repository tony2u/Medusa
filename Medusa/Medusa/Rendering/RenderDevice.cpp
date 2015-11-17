// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderDevice.h"

MEDUSA_BEGIN;

RenderDevice::RenderDevice()
{
	mCurrentThreadHandle = 0;
}

RenderDevice::~RenderDevice(void)
{

}

bool RenderDevice::Initialize(bool disableThreading /*= false*/)
{
	bool result = BaseFrameCommandProcessor::Initialize(disableThreading);
	if (!disableThreading)
	{
		mCurrentThreadHandle = mThread.Handle();
	}
	else
	{
		mCurrentThreadHandle = Thread::Current();
	}
	return result;
}

bool RenderDevice::Uninitialize()
{
	return BaseFrameCommandProcessor::Uninitialize();
}

bool RenderDevice::NeedAsync() const
{
	return !Thread::IsThreadEqual(mCurrentThreadHandle, Thread::Current());
}

MEDUSA_END;