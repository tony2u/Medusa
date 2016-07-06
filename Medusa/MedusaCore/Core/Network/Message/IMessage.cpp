// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IMessage.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


IMessage::IMessage(uint fromServiceId/* = 0*/, uint toServcieId /*= 0*/)
	:ICommand(fromServiceId, toServcieId)
{
	mTimeoutWatch.Start();
}


IMessage::~IMessage(void)
{
}

bool IMessage::CheckTimeout()
{
	return mTimeoutWatch.ElapsedMilliseconds() >= mMillisecondsTimeout;
}

bool IMessage::IsRequest() const
{
	return !IsResponse();
}

bool IMessage::IsResponse() const
{
	return Behavior() == MessageBehavior::Response;
}


MessageBehavior IMessage::Behavior() const
{
	/*
	Id!=0 && SessionId!=0 : Request need response
	Id!=0 && SessionId==0 : Request without response

	Id==0 && SessionId!=0 : Reponse to request
	Id==0 && SessionId==0 : Heartbeat without response
	*/

	if (mId == 0)
	{
		if (mSessionId == 0)
		{
			return MessageBehavior::HeartbeatWithoutResponse;
		}
		return MessageBehavior::Response;
	}
	else
	{
		if (mSessionId == 0)
		{
			return MessageBehavior::RequestWithoutResponse;
		}
		return MessageBehavior::RequestResponse;
	}
}

bool IMessage::OnSend(MessageSocketConnection& connection)
{
	OnSendEvent(*this, connection);
	return true;
}

bool IMessage::OnRequest(MessageSocketConnection& connection)
{
	OnRequestEvent(*this, connection);
	return true;
}

bool IMessage::OnResponse(MessageSocketConnection& connection)
{
	OnResponseEvent(*this, connection);
	return true;
}



MEDUSA_END;
