// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "PerformanceCounter.h"


MEDUSA_BEGIN;

class StopWatch
{
public:
	StopWatch(const StringRef& name = StringRef::Empty, size_t runTimes = 1, bool enabled = true);
public:
	void Start();
	void Shot();
	void Step();
	void Reset();
	void TraceResult()const;
	void PrintResult()const;

public:
	int64 ElapsedTicks() const { return mEnabled ? mElapsedTime : 0; }
	float ElapsedSeconds()const;
	float ElapsedMilliseconds()const;

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	size_t RunTimes() const { return mRunTimes; }
	void SetRunTimes(size_t val) { mRunTimes = val; }

	bool IsEnabled() const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }
private:
	HeapString mName;

	size_t mRunTimes;

	ProfileTimeType mStartTime;
	ProfileTimeType mEndTime;

	ProfileTimeType mElapsedTime;
	bool mEnabled;

};


MEDUSA_END;