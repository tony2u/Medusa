// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/String/StringRef.h"
#include "Core/Collection/List.h"
#include "Core/Profile/PerformanceCounter.h"

MEDUSA_BEGIN;

class ProfileNode
{
public:
	ProfileNode(const StringRef& name,ProfileNode* parent,size_t count=1,size_t logCount=0);
	~ProfileNode();
public:
	void Begin();
	bool End();
	void Reset();

	void Stop();
	ProfileNode* FindOrCreateChildNode(const StringRef& name,size_t count=1,size_t logCount=0);
	void PrintResult(const StringRef& totalPrefix,const StringRef& perPrefix)const;


public:
	const StringRef& Name() const { return mName; }
	ProfileNode* Parent() const { return mParent; }

private:
	StringRef mName;
	ProfileNode* mParent;
	List<ProfileNode*> mChildren;
	size_t mTestCount;

	size_t mTotalCount;
	ProfileTimeType mTotalTime;
	ProfileTimeType mStartTime;
	int mRecursionCounter;

	List<int64> mTimeLogs;
	size_t mMinLogIndex;
	size_t mMaxLogIndex;

	ProfileTimeType mMinTime;
	ProfileTimeType mMaxTime;

};


MEDUSA_END;