// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Threading/IWaitable.h"
#include "Core/Threading/posix/ThreadEventImp_posix.h"
#include "Core/Threading/win/ThreadEventImp_win.h"
#include "Core/Pattern/INonCopyable.h"


MEDUSA_BEGIN;

class ThreadEvent :public ThreadEventImp, public IWaitable,public INonCopyable
{
public:
	ThreadEvent(bool autoReset = true, bool isSet = false, bool isInitializeNow = true);
	~ThreadEvent();
	void Initialize(bool autoReset = true, bool isSet = false);
	void Uninitialize();

	virtual void Set()override;
	void Reset();
	bool IsAutoReset() const { return mIsAutoReset; }

	bool IsSet()const;
	virtual bool Wait()override;
	virtual bool TryWait()override;
	virtual bool WaitFor(long milliseconds)override;

#ifdef MEDUSA_THREADING_MULTIPLE_WAIT
	static bool WaitForMultipleEvents(const List<ThreadEvent*>& events, bool waitAll, long milliseconds,int& outWaitIndex);
#endif

#ifndef MEDUSA_POSIX_THREADING
	virtual ThreadNativeHandle NativeHandle()const override { return mEvent; }
#endif
};




MEDUSA_END;
