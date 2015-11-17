// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Math/Math.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;

StopWatch::StopWatch(const StringRef& name,size_t runTimes/*=1*/,bool enabled/*=true*/):mName(name),mRunTimes(runTimes),mStartTime(0),mEndTime(0),mElapsedTime(0),mEnabled(enabled)
{
}


void StopWatch::Start()
{
	RETURN_IF_FALSE(mEnabled);
	mStartTime= PerformanceCounter::Ticks();
}

void StopWatch::Step()
{
	RETURN_IF_FALSE(mEnabled);
	mEndTime = PerformanceCounter::Ticks();
	mElapsedTime = mEndTime - mStartTime;
	mStartTime = mEndTime;
}

void StopWatch::Shot()
{
	RETURN_IF_FALSE(mEnabled);
	mEndTime= PerformanceCounter::Ticks();
	mElapsedTime=mEndTime-mStartTime;
}

void StopWatch::Reset()
{
	mStartTime=0;
	mEndTime=0;
	mElapsedTime=0;

}

float StopWatch::ElapsedSeconds() const
{
	return mEnabled ? (float)PerformanceCounter::Instance().ToMilliseconds(mElapsedTime)*1000.f  : 0.f;
}

float StopWatch::ElapsedMilliseconds() const
{
	return mEnabled ? (float)PerformanceCounter::Instance().ToMilliseconds(mElapsedTime)  : 0.f;
}

void StopWatch::TraceResult() const
{
	RETURN_IF_FALSE(mEnabled);
	float dt=ElapsedMilliseconds();

	WHeapString str(L"???");
	if (!mName.IsEmpty())
	{
		WHeapString temp=StringParser::ToW(mName);

		str.AppendFormat(L"{}\t", temp.Buffer());
	}

	if (mRunTimes>0&&dt!=0)
	{
		str.AppendFormat(L"{} / {} = {}",dt,mRunTimes,dt/mRunTimes);
	}

	str+='\n';
	MEDUSA_TRACEW(str.Buffer());
}


void StopWatch::PrintResult() const
{
	RETURN_IF_FALSE(mEnabled);
	float dt = ElapsedMilliseconds();

	HeapString str("???");
	if (!mName.IsEmpty())
	{
		str.AppendFormat("{}\t", mName.Buffer());
	}

	if (mRunTimes > 0 && dt != 0)
	{
		str.AppendFormat("{} / {} = {}", dt, mRunTimes, dt / mRunTimes);
	}

	str += '\n';
	printf(str.Buffer());
}

MEDUSA_END;

