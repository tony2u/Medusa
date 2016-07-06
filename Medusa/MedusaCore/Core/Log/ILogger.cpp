// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ILogger.h"
#include "Core/String/StdString.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Log/LogMessagePool.h"

MEDUSA_BEGIN;

ILogger::ILogger(StringRef name /*= StringRef::Empty*/)
	:mName(name)
{
	mCurrentThread = Thread::CurrentId();
}

ILogger::~ILogger(void)
{
}


void ILogger::Add(const Share<LogMessage>& message)
{

	if (IsCurrentThread())
	{
		Print(message);
	}
	else
	{
		ScopedLock lock(mMutex);
		mMessageList.MutableBack().Add(message);
	}
}

void ILogger::Add(const Share<WLogMessage>& message)
{
	if (IsCurrentThread())
	{
		Print(message);
	}
	else
	{
		ScopedLock lock(mMutex);
		mWMessageList.MutableBack().Add(message);
	}
}

void ILogger::Update(float dt /*= 0.f*/)
{
	if (IsCurrentThread())
	{
		ScopedLock lock(mMutex);

		{
			mMessageList.Swap();
			auto& messages = mMessageList.MutableFront();
			if (!messages.IsEmpty())
			{
				for (const auto& item : messages)
				{
					Print(item);
				}
				messages.Clear();
			}
		}
		
		{
			mMessageList.Swap();
			auto& messages = mWMessageList.MutableFront();
			if (!messages.IsEmpty())
			{
				for (const auto& item : messages)
				{
					Print(item);
				}
				messages.Clear();
			}
		}
	}
}

bool ILogger::IsCurrentThread() const
{
	return Thread::IsCurrent(mCurrentThread);
}



MEDUSA_END;
