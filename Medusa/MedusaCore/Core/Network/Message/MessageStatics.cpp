// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MessageStatics.h"
#include "Core/Network/Message/IMessage.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

MessageStatics::MessageStatics()
{
	
}

MessageStatics::~MessageStatics(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mMessages);
}

void MessageStatics::BeginRequestSend(uint id, uint sessionId)
{
	auto node = FindOrCreate(id);
	node->SessionId = sessionId;
	node->RequestSend.Begin();
	node->RequestResponse.Begin();

}

void MessageStatics::EndRequestSend(uint id, uint sessionId)
{
	auto node = FindOrCreate(id);
	node->RequestSend.End();
}

void MessageStatics::BeginResponseSend(uint id, uint sessionId)
{
	auto node = FindOrCreate(id);
	node->ResponseSend.Begin();
}

void MessageStatics::EndResponseSend(uint id, uint sessionId)
{
	auto node = FindOrCreate(id);
	node->ResponseSend.End();
	node->Print(mIsClient);
}

void MessageStatics::BeginWrite(const ShareMessage& message)
{
	if (message->IsRequest())
	{
		BeginRequestSend(message->StaticId(),message->SessionId());
	}
	else
	{
		BeginResponseSend(message->StaticId(), message->SessionId());
	}
}


void MessageStatics::EndWrite(const ShareMessage& message)
{
	if (message->IsRequest())
	{
		EndRequestSend(message->StaticId(), message->SessionId());
	}
	else
	{
		EndResponseSend(message->StaticId(), message->SessionId());
	}
}

void MessageStatics::OnRequestReceive(const ShareMessage& message, StopWatch::Duration time)
{
	auto node = FindOrCreate(message->StaticId());
	node->RequestReceive.Count(time);
	node->SessionId = message->SessionId();
}

void MessageStatics::OnResponseReceive(const ShareMessage& message, StopWatch::Duration time)
{
	auto node = FindOrCreate(message->StaticId());
	node->ResponseReceive.Count(time);
	node->RequestResponse.End();
	node->Print(mIsClient);
}

MessageStatics::MessageNode* MessageStatics::FindOrCreate(uint id)
{
	auto node= mMessages.GetOptional(id, nullptr);
	if (node==nullptr)
	{
		node = new MessageNode();
		node->Id = id;
		mMessages.Add(id, node);
	}
	return node;
}

void MessageStatics::MessageNode::Print(bool isClient) const
{
	if (isClient)
	{
		auto averageTime =StopWatch::ToMilliseconds(RequestResponse.AverageTime());
		auto minTime = StopWatch::ToMilliseconds(RequestResponse.MinTime());
		auto maxTime = StopWatch::ToMilliseconds(RequestResponse.MaxTime());
		auto elapsedTime = StopWatch::ToMilliseconds(RequestResponse.ElapsedTime());
		Log::FormatInfo("{} {}: {:f6} - {:f6} - {:f6} = {:f6}", Id,SessionId, minTime, averageTime,maxTime, elapsedTime);
	}
	else
	{
		auto averageTime = StopWatch::ToMilliseconds(RequestReceive.AverageTime()+ ResponseSend.AverageTime());
		auto minTime = StopWatch::ToMilliseconds(RequestReceive.MinTime() + ResponseSend.AverageTime());
		auto maxTime = StopWatch::ToMilliseconds(RequestReceive.MaxTime() + ResponseSend.AverageTime());
		auto elapsedTime = StopWatch::ToMilliseconds(RequestReceive.ElapsedTime() + ResponseSend.AverageTime());
		Log::FormatInfo("{} {}: {:f6} - {:f6} - {:f6} = {:f6}", Id, SessionId, minTime, averageTime, maxTime, elapsedTime);
	}

}

MEDUSA_END;

