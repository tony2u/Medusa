// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;

typedef uint64 ProfileTimeType;

#ifdef MEDUSA_IOS
typedef mach_timebase_info_data_t ProfileFreqType;
#else
typedef uint64 ProfileFreqType;
#endif

class PerformanceCounter :public Singleton<PerformanceCounter>
{
	friend class Singleton<PerformanceCounter>;
	PerformanceCounter();
	~PerformanceCounter(void) = default;
public:
	double ToMilliseconds(ProfileTimeType time)const;
	static ProfileTimeType Ticks();
	static timespec ToAbsoluteTime(int64 millisecondsFromNow);
private:
	ProfileFreqType mFreq;
};

MEDUSA_END;
