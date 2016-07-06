// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Chrono/ProfileNode.h"
#include "Core/Math/Math.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

ProfileNode::ProfileNode(const StringRef& name, ProfileNode* parent, size_t count/*=1*/, size_t logCount/*=0*/)
	:mName(name), mParent(parent), mCount(count), mTimeLogs(logCount)
{
	if (logCount > 0)
	{
		mTimeLogs.ReserveSize(logCount);
	}
}

ProfileNode::ProfileNode()
{

}

ProfileNode::~ProfileNode()
{
	SAFE_DELETE_COLLECTION(mChildren);
}

void ProfileNode::Begin()
{
	if (mRecursionCounter++ == 0)
	{
		mStartTime = StopWatch::ClockType::now();
	}
}


bool ProfileNode::End()
{
	if (--mRecursionCounter == 0)
	{
		mEndTime = StopWatch::ClockType::now();
		mElapsedTime = mEndTime - mStartTime;
		Count(mElapsedTime);
	}
	return (mRecursionCounter == 0);
}

bool ProfileNode::End(StopWatch::TimePoint currentTime)
{
	if (--mRecursionCounter == 0)
	{
		mEndTime = currentTime;
		mElapsedTime = currentTime - mStartTime;
		Count(mElapsedTime);
	}
	return (mRecursionCounter == 0);
}

bool ProfileNode::Count(StopWatch::Duration elapsedTime)
{
	++mTotalCount;
	mElapsedTime = elapsedTime;
	mTotalTime += elapsedTime;
	if (elapsedTime < mMinTime)
	{
		mMinTime = elapsedTime;
		mMinLogIndex = mTimeLogs.Count();
	}
	if (elapsedTime > mMaxTime)
	{
		mMaxTime = elapsedTime;
		mMaxLogIndex = mTimeLogs.Count();
	}

	if (!mTimeLogs.IsFull())
	{
		mTimeLogs.Add(elapsedTime.count());
	}
	return true;
}

void ProfileNode::Reset()
{
	mTotalCount = 0;
	mRecursionCounter = 0;
	mMinLogIndex = 0;
	mMaxLogIndex = 0;
	mTimeLogs.Clear();

	mTotalTime = StopWatch::Duration(0);
	mElapsedTime = StopWatch::Duration(0);

	mMinTime = StopWatch::Duration(Math::UInt64MaxValue);
	mMaxTime = StopWatch::Duration(0);

	for (auto node : mChildren)
	{
		node->Reset();
	}
}


void ProfileNode::Stop()
{
	for (auto node : mChildren)
	{
		node->End();
	}
	End();
}

ProfileNode* ProfileNode::FindOrCreateChildNode(const  StringRef& name, size_t count/*=1*/, size_t logCount/*=1*/)
{
	size_t size = mChildren.Count();
	FOR_EACH_SIZE(i, size)
	{
		ProfileNode* node = mChildren[i];
		if (node->Name().IsRefEqualsTo(name))
		{
			return node;
		}
	}

	ProfileNode* newNode = new ProfileNode(name, this, count, logCount);
	mChildren.Append(newNode);
	return newNode;
}



void ProfileNode::PrintResult(const StringRef& totalPrefix, const StringRef& perPrefix) const
{

	double dt = StopWatch::ToMilliseconds(mTotalTime) / (double)mCount;	//ms
	double minTime = StopWatch::ToMilliseconds(mMinTime) / (double)mCount;	//ms
	double maxTime = StopWatch::ToMilliseconds(mMaxTime) / (double)mCount;	//ms

	HeapString str = totalPrefix;

	if (!mName.IsEmpty())
	{
		if (mCount != 1)
		{
			str.AppendFormat("{}/{}\t", mName.Buffer(), mCount);
		}
		else
		{
			str.AppendFormat("{}\t", mName.Buffer());
		}

	}

	if (dt != 0)
	{
		if (mTotalCount > 1)
		{
			str.AppendFormat("{} / {} = {} {}->{}   ", dt, mTotalCount, dt / mTotalCount, minTime, maxTime);
		}
		else
		{
			str.AppendFormat("{}  ", dt);
		}
	}

	if (mTotalCount > 0 && dt != 0)
	{
	}

	if (!mTimeLogs.IsEmpty())
	{
		size_t logCount = mTimeLogs.Count();
		str.AppendFormat("{}:[", logCount);

		FOR_EACH_SIZE(i, logCount)
		{

			double logTime = (double)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds(mTimeLogs[i])).count() / mCount);	//ms
			if (i == mMinLogIndex)
			{
				str += '#';
				str += StringParser::ToString(logTime);
				str += '#';
			}
			else if (i == mMaxLogIndex)
			{
				str += '#';
				str += StringParser::ToString(logTime);
				str += '#';
			}
			else
			{
				str += StringParser::ToString(logTime);
			}
			if (i != logCount - 1)
			{
				str += ' ';
			}
		}
		str += "]";
	}



	str += '\n';
	Log::Info(str);

	HeapString totalPrefixCopy = totalPrefix;
	totalPrefixCopy += perPrefix;

	for (auto node : mChildren)
	{
		node->PrintResult(totalPrefixCopy, perPrefix);
	}
}


MEDUSA_END;