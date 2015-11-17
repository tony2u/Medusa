// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Profile/ProfileNode.h"
#include "Core/Math/Math.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;

ProfileNode::ProfileNode(const StringRef& name,ProfileNode* parent,size_t count/*=1*/ ,size_t logCount/*=0*/)
	:mName(name),mParent(parent),mTestCount(count),mTimeLogs(logCount)
{
	mTotalCount=0;
	mStartTime=0;
	mTotalTime=0;
	mRecursionCounter=0;
	mMinTime=Math::UIntMaxValue;
	mMaxTime=Math::UIntMinValue;
	mMinLogIndex=0;
	mMaxLogIndex=0;

	if (logCount>0)
	{
		mTimeLogs.ReserveSize(logCount);
	}
}

ProfileNode::~ProfileNode()
{
	SAFE_DELETE_COLLECTION(mChildren);
}

void ProfileNode::Begin()
{
	++mTotalCount;
	if (mRecursionCounter++==0)
	{
		mStartTime= PerformanceCounter::Ticks();
	}
}


bool ProfileNode::End()
{
	if ( --mRecursionCounter == 0 && mTotalCount != 0 )
	{
		ProfileTimeType currentTime= PerformanceCounter::Ticks();
		ProfileTimeType elapsedTime=currentTime-mStartTime;
       
		mTotalTime+=elapsedTime;
		if (elapsedTime<mMinTime)
		{
			mMinTime=elapsedTime;
			mMinLogIndex=mTimeLogs.Count();
		}
		if (elapsedTime>mMaxTime)
		{
			mMaxTime=elapsedTime;
			mMaxLogIndex=mTimeLogs.Count();
		}

		if (!mTimeLogs.IsFull())
		{
			mTimeLogs.Add(elapsedTime);
		}
	}
	return ( mRecursionCounter == 0 );
}

void ProfileNode::Reset()
{
	mTotalCount=0;
	mStartTime=0;
	mTotalTime=0;
	mMinTime=Math::UIntMaxValue;
	mMaxTime=Math::UIntMinValue;
	mRecursionCounter=0;
	mMinLogIndex=0;
	mMaxLogIndex=0;
	mTimeLogs.Clear();

	FOR_EACH_COLLECTION(i,mChildren)
	{
		ProfileNode* node=*i;
		node->Reset();
	}
}


void ProfileNode::Stop()
{
	FOR_EACH_COLLECTION(i,mChildren)
	{
		ProfileNode* node=*i;
		node->End();
	}
	End();
}

ProfileNode* ProfileNode::FindOrCreateChildNode(const  StringRef& name ,size_t count/*=1*/,size_t logCount/*=1*/)
{
	size_t size=mChildren.Count();
	FOR_EACH_SIZE(i,size)
	{
		ProfileNode* node=mChildren[i];
		if (node->Name().IsRefEqualsTo(name))
		{
			return node;
		}
	}

	ProfileNode* newNode=new ProfileNode(name,this,count,logCount);
	mChildren.Append(newNode);
	return newNode;
}



void ProfileNode::PrintResult(const StringRef& totalPrefix,const StringRef& perPrefix) const
{
	
	double dt= PerformanceCounter::Instance().ToMilliseconds(mTotalTime) /mTestCount;	//ms
	double minTime= PerformanceCounter::Instance().ToMilliseconds(mMinTime) /mTestCount;	//ms
	double maxTime= PerformanceCounter::Instance().ToMilliseconds(mMaxTime) /mTestCount;	//ms

	HeapString str=totalPrefix;

	if (!mName.IsEmpty())
	{
		if (mTestCount!=1)
		{
			str.AppendFormat("{}/{}\t",mName.Buffer(),mTestCount);
		}
		else
		{
			str.AppendFormat("{}\t",mName.Buffer());
		}

	}

	if (dt!=0)
	{
		if (mTotalCount>1)
		{
			str.AppendFormat("{} / {} = {} {}->{}   ",dt,mTotalCount,dt/mTotalCount,minTime,maxTime);
		}
		else
		{
			str.AppendFormat("{}  ",dt);
		}
	}

	if (mTotalCount>0&&dt!=0)
	{
	}

	if (!mTimeLogs.IsEmpty())
	{
		size_t logCount=mTimeLogs.Count();
		str.AppendFormat("{}:[",logCount);

		FOR_EACH_SIZE(i,logCount)
		{
			double logTime= PerformanceCounter::Instance().ToMilliseconds(mTimeLogs[i]) /mTestCount;	//ms
			if (i==mMinLogIndex)
			{
				str+='#';
				str+=StringParser::ToString(logTime);
				str+='#';
			}
			else if (i==mMaxLogIndex)
			{
				str+='#';
				str+=StringParser::ToString(logTime);
				str+='#';
			}
			else
			{
				str+=StringParser::ToString(logTime);
			}
			if (i!=logCount-1)
			{
				str+=' ';
			}
		}
		str+="]";
	}



	str+='\n';
	MEDUSA_TRACE(str.Buffer());

	HeapString totalPrefixCopy=totalPrefix;
	totalPrefixCopy+=perPrefix;

	FOR_EACH_COLLECTION(i,mChildren)
	{
		const ProfileNode* node=*i;
		node->PrintResult(totalPrefixCopy,perPrefix);
	}
}


MEDUSA_END;