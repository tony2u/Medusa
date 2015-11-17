// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Message/Handler/MockMessageHandler.h"
#include "Core/Log/Log.h"
#include "Core/Message/Handler/MessageHandlerFactory.h"
#include "Core/Profile/AutoStopWatch.h"

MEDUSA_BEGIN;

MockMessageHandler::MockMessageHandler(size_t id, StringRef hostName, ushort port, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey)
	:IMessageHandler(id,hostName,port,retryTimes,retryInternal,messageVersion,sendCoderType,receiveCoderType,encryptKey)
{

}

MockMessageHandler::~MockMessageHandler()
{

}


void MockMessageHandler::Process()
{
	AutoStopWatch autoTotalStopWatch(mTotalStopWatch);
	while(mMessageQueue.Count()>0)
	{
		IMessage* message=mMessageQueue.Head();
		mMessageQueue.Pop();
		SendMessage(message);
		SAFE_RELEASE(message);
	}
}

IMessage* MockMessageHandler::SendMessage( IMessage* message )
{
	
	FireUIEventAsync(message->SendHandler(),message);

	message->Mock();
	message->SetState(MessageState::Completed);
	if (!message->HasResponse())
	{
		Log::FormatError("Cannot implement Mock on message:{}",message->Class().Name().c_str());
		message->SetState(MessageState::ConnectFail);
		FireUIEventAsync(message->ReceiveHandler(),message);
		return message;
	}

	message->SetState(MessageState::Completed);
	StringRef expectedResponseClassName=message->ResponseClassName();
	Log::FormatInfo("Receive:{}",expectedResponseClassName.c_str());
	FireUIEventAsync(message->ReceiveHandler(),message);

	return message;

}





MEDUSA_END;
