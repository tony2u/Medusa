// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Threading/IWaitable.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

class Semaphore :public SemaphoreImp, public IWaitable
{
public:
	Semaphore(uint initialValue = 0, uint maxLimit = Math::UIntMaxValue, bool isInitializeNow = true);
	~Semaphore();
	void Initialize(uint initialValue = 0, uint maxLimit = Math::UIntMaxValue);
	void Uninitialize();

	void Set(uint count);
	virtual void Set()override;

	virtual bool Wait()override;
	virtual bool TryWait()override;
	virtual bool WaitTimeout(long milliseconds)override;
#ifndef MEDUSA_POSIX_THREADING
	virtual ThreadNativeHandle NativeHandle()const override { return mSem; }
#endif
private:
	Semaphore(const Semaphore &);
	Semaphore& operator=(const Semaphore &);

};


MEDUSA_END;
