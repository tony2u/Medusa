// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Profile/PerformanceCounter.h"
#ifdef MEDUSA_ANDROID

MEDUSA_BEGIN;

PerformanceCounter::PerformanceCounter()
{
	mFreq = 1;
}

ProfileTimeType PerformanceCounter::Ticks()
{
	struct timeval t;

	gettimeofday(&t, nullptr);
	t.tv_sec %= 86400; // one day ticks 24*60*60

	return (t.tv_sec * 1000 + t.tv_usec);
}

double PerformanceCounter::ToMilliseconds(ProfileTimeType time) const
{
	return (double)time / mFreq;
}


timespec PerformanceCounter::ToAbsoluteTime(int64 millisecondsFromNow)
{
	struct timespec abstime;
	struct timeval tv;
	gettimeofday(&tv, nullptr);

	abstime.tv_sec = tv.tv_sec + millisecondsFromNow / 1000;
	abstime.tv_nsec = tv.tv_usec * 1000 + (millisecondsFromNow % 1000) * 1000000;
	if (abstime.tv_nsec >= 1000000000)
	{
		abstime.tv_nsec -= 1000000000;
		abstime.tv_sec++;
	}
	return abstime;
}
MEDUSA_END;

#endif