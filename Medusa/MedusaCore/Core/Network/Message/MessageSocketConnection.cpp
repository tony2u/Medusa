// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MessageSocketConnection.h"
#include "Core/Log/Log.h"
#include "Core/Network/Message/MessageFactory.h"
#include "Core/Network/Message/MessageStatics.h"
#include "Core/Network/Socket/SocketPeer.h"

MEDUSA_BEGIN;

MessageSocketConnection::MessageSocketConnection(SocketPeer* peer, EventLoop* loop, const Socket& socket)
	:BaseType(peer,loop,socket)
{
	MessageStatics::Instance().SetClient(peer->IsClient());
}

MessageSocketConnection::~MessageSocketConnection(void)
{

}

bool MessageSocketConnection::OnHandleRead()
{
	RETURN_FALSE_IF(mReadBuffer.ReadableCount() < sizeof(uint32));
	uint32 size = mReadBuffer.Peek<uint32>();
	RETURN_FALSE_IF(size > mReadBuffer.ReadableCount() - sizeof(uint32));

	StopWatch watch;
	watch.Start();
	//receive message
	mReadBuffer.Retrieve<uint>();	//size header
	uint fromServiceId = mReadBuffer.Read<uint>();
	uint toServiceId = mReadBuffer.Read<uint>();
	uint version = mReadBuffer.Read<uint>();
	uint id = mReadBuffer.Read<uint>();
	uint sessionId = mReadBuffer.Read<uint>();
	uint connectionId = mReadBuffer.Read<uint>();

	size_t dataSize = size - sizeof(int32_t) * 6;
	auto data = mReadBuffer.ReadData(dataSize, DataReadingMode::DirectMove);

	if (id != 0)
	{
		auto out = MessageFactory::Instance().Create(id);
		if (out == nullptr)
		{
			Log::AssertFailedFormat("Failed to create message with id:{}", id);
			return false;
		}
		out->SetFromService(fromServiceId);
		out->SetToService(toServiceId);
		out->SetVersion(version);
		out->SetSessionId(sessionId);
		out->SetConnectionId(connectionId);
		if (out->DeserializeRequest(data))
		{
			out->OnRequest(*this);

			if (sessionId != 0)
			{
				Math::Swap(out->MutableFromService(), out->MutableToService());	//send back
				out->SetId(0);

				watch.Shot();
				MessageStatics::Instance().OnRequestReceive(out, watch.ElapsedTime());
				Write(out);
			}
			else
			{
				//Request without response
				watch.Shot();
				MessageStatics::Instance().OnRequestReceive(out, watch.ElapsedTime());
			}
		}
		else
		{
			auto messageName = MessageFactory::Instance().GetName(id);
			Log::FormatError("{}- Invalid request data.fromServiceId:{},toServiceId:{},version:{},id:{},sessionId:{}", messageName, fromServiceId, toServiceId, version, id, sessionId);
			return false;
		}

	}
	else
	{
		//response from server
		if (sessionId != 0)
		{
			auto prevMessage = TryRemoveSession(sessionId);
			if (prevMessage != nullptr)
			{
				prevMessage->DeserializeResponse(data);
				prevMessage->SetId(0);	//indicate a response
				prevMessage->OnResponse(*this);
				watch.Shot();
				MessageStatics::Instance().OnResponseReceive(prevMessage, watch.ElapsedTime());

			}
			else
			{
				//cannot find the session id, maybe this command has timeout,but we also have to trigger a warning
				Log::AssertFailedFormat("Got a response after timeout.id:{} sessionId:{}", id, sessionId);
			}
		}
		else
		{
			//heart beat request from client
			//do nothing
			//Log::Info("Heartbeat");


		}
	}


	return true;
}

bool MessageSocketConnection::OnHandleWrite(const ShareMessage& message)
{
	MessageStatics::Instance().BeginWrite(message);

	StopWatch watch;
	watch.Start();

	message->SetConnectionId(mId);
	if (message->Behavior() == MessageBehavior::RequestResponse && message->NeedResponse())
	{
		mMessageSessions.Add(message->SessionId(), message);
	}

	message->OnSend(*this);

	MemoryData data;
	if (message->IsRequest())
	{
		data = message->SerializeRequest();
		if (data.IsEmpty())
		{
			Log::FormatError("Cannot serialize request:{}", message->Id());
			return false;
		}

	}
	else
	{
		data = message->SerializeResponse();
		if (data.IsEmpty())
		{
			Log::FormatError("Cannot serialize response:{}", message->Id());
			return false;
		}
	}


	size_t size = data.ByteSize() + sizeof(int32_t) * 6;
	mWriteBuffer.Write(size);
	mWriteBuffer.Write(message->FromService());
	mWriteBuffer.Write(message->ToService());
	mWriteBuffer.Write(message->Version());
	mWriteBuffer.Write(message->Id());
	mWriteBuffer.Write(message->SessionId());
	mWriteBuffer.Write(message->ConnectionId());
	mWriteBuffer.Write(data.Data(), data.ByteSize());


	//mSocket.SendAsync(mWriteBuffer);
	if (mWriteBuffer.ReadableCount() > 0)
	{
		AddCaredEvents(ChannelEventFlags::Write);
	}

	MessageStatics::Instance().EndWrite(message);
	return true;
}


ShareMessage MessageSocketConnection::TryRemoveSession(uint sessionId)
{
	return mMessageSessions.RemoveKeyOptional(sessionId, nullptr);

}

MEDUSA_END;