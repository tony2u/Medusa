// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifndef MEDUSA_POSIX_THREADING

#include "Core/Threading/Semaphore.h"

MEDUSA_BEGIN;

Semaphore::Semaphore(uint initialValue/*=0*/, uint maxLimit /*= Math::UIntMaxValue*/, bool isInitializeNow /*= true*/)
{
	if (isInitializeNow)
	{
		Initialize(initialValue, maxLimit);
	}
}

Semaphore::~Semaphore()
{
	Uninitialize();
}

void Semaphore::Initialize(uint initialValue/*=0*/, uint maxLimit /*=Math::UIntMaxValue*/)
{
	if (mSem == nullptr)
	{
		mSem = CreateSemaphoreW(nullptr, initialValue, maxLimit, nullptr);
	}
}

void Semaphore::Uninitialize()
{
	if (mSem != nullptr)
	{
		CloseHandle(mSem);
		mSem = nullptr;
	}

}

void Semaphore::Set(uint count)
{
	ReleaseSemaphore(mSem, count, nullptr);
}

void Semaphore::Set()
{
	Set(1);
}

bool Semaphore::Wait()
{
	return WaitForSingleObject(mSem, INFINITE) == WAIT_OBJECT_0;
}

bool Semaphore::TryWait()
{
	return WaitForSingleObject(mSem, 0) == WAIT_OBJECT_0;
}
bool Semaphore::WaitTimeout(long milliseconds)
{
	return WaitForSingleObject(mSem, milliseconds) == WAIT_OBJECT_0;

}

MEDUSA_END;
#endif