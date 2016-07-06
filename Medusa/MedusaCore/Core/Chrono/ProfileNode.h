// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/String/StringRef.h"
#include "Core/Collection/List.h"
#include "Core/Chrono/StopWatch.h"

MEDUSA_BEGIN;

class ProfileNode
{
public:
	ProfileNode(const StringRef& name, ProfileNode* parent, size_t count = 1, size_t logCount = 0);
	ProfileNode();
	~ProfileNode();
public:
	void Begin();
	bool End();
	bool End(StopWatch::TimePoint timeStamp);
	bool Count(StopWatch::Duration elapsedTime);

	void Reset();

	void Stop();
	ProfileNode* FindOrCreateChildNode(const StringRef& name, size_t count = 1, size_t logCount = 0);
	void PrintResult(const StringRef& totalPrefix, const StringRef& perPrefix)const;


public:
	const StringRef& Name() const { return mName; }
	ProfileNode* Parent() const { return mParent; }
	StopWatch::Duration AverageTime()const { return mTotalCount!=0?mTotalTime / mTotalCount / mCount: StopWatch::Duration(0); }
	StopWatch::Duration MinTime()const { return mTotalCount != 0 ? mMinTime / mCount : StopWatch::Duration(0); }
	StopWatch::Duration MaxTime()const { return mTotalCount != 0 ? mMaxTime / mCount : StopWatch::Duration(0); }

	StopWatch::Duration ElapsedTime()const { return mElapsedTime / mCount; }

private:
	StringRef mName;
	ProfileNode* mParent = nullptr;
	List<ProfileNode*> mChildren;
	size_t mCount = 1;	//each run count

	size_t mTotalCount = 0;
	StopWatch::Duration mTotalTime{ 0 };
	StopWatch::TimePoint mStartTime;
	StopWatch::TimePoint mEndTime;
	StopWatch::Duration mElapsedTime{ 0 };

	int mRecursionCounter = 0;

	List<int64> mTimeLogs;
	size_t mMinLogIndex = 0;
	size_t mMaxLogIndex = 0;

	StopWatch::Duration mMinTime{ Math::UIntMaxValue };
	StopWatch::Duration mMaxTime{ 0 };

};


MEDUSA_END;