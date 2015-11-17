// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Profile/PerformanceCounter.h"
#ifdef MEDUSA_WINDOWS

MEDUSA_BEGIN;

PerformanceCounter::PerformanceCounter()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	mFreq= freq.QuadPart;
}

ProfileTimeType PerformanceCounter::Ticks()
{
	LARGE_INTEGER prev;
	QueryPerformanceCounter(&prev);
	return prev.QuadPart;
}

double PerformanceCounter::ToMilliseconds(ProfileTimeType time) const
{
	return ((double)time / mFreq)*1000;
}


timespec PerformanceCounter::ToAbsoluteTime(int64 millisecondsFromNow)
{
	struct timespec abstime;
	struct timeval tv;

	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	struct tm tm;
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	time_t clock = mktime(&tm);
	tv.tv_sec = (long)clock;
	tv.tv_usec = wtm.wMilliseconds * 1000;

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