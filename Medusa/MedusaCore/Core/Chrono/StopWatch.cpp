// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Chrono/StopWatch.h"
#include "Core/Math/Math.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

StopWatch::StopWatch(const StringRef& name, size_t runTimes/*=1*/, bool enabled/*=true*/)
	:mName(name), mRunTimes(runTimes), mEnabled(enabled)
{
	Reset();
}


void StopWatch::Start()
{
	RETURN_IF_FALSE(mEnabled);
	mStartTime = ClockType::now();
}

void StopWatch::Step()
{
	RETURN_IF_FALSE(mEnabled);
	mEndTime = ClockType::now();
	mElapsedTime = mEndTime - mStartTime;
	mStartTime = mEndTime;
}

void StopWatch::Go()
{
	RETURN_IF_FALSE(mEnabled);
	mStartTime = mEndTime;
}


void StopWatch::Shot()
{
	RETURN_IF_FALSE(mEnabled);
	mEndTime = ClockType::now();
	mElapsedTime = mEndTime - mStartTime;
}

void StopWatch::Reset()
{
	mStartTime = ClockType::now();
	mEndTime = mStartTime;
	mElapsedTime = Duration(0);

}

void StopWatch::ResetToNow()
{
	Reset();
	Start();
}

float StopWatch::ElapsedSeconds() const
{
	return mEnabled ? ToSeconds(mElapsedTime) : 0.f;
}

float StopWatch::ElapsedMilliseconds() const
{
	return mEnabled ? ToMilliseconds(mElapsedTime) : 0.f;
}

float StopWatch::ToMilliseconds(Duration val)
{
	return val.count()*0.000001f;
}

float StopWatch::ToSeconds(Duration val)
{
	return val.count()*0.000000001f;
}



void StopWatch::PrintResult() const
{
	RETURN_IF_FALSE(mEnabled);
	float dt = ElapsedMilliseconds();

	HeapString str("***");
	if (!mName.IsEmpty())
	{
		str.AppendFormat("{}\t", mName.Buffer());
	}

	if (mRunTimes > 0 && dt != 0)
	{
		str.AppendFormat("{} / {} = {}", dt, mRunTimes, dt / mRunTimes);
	}

	str += '\n';
	Log::Info(str);
}

MEDUSA_END;

