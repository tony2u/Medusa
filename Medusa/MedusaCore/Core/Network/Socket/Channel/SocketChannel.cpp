// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SocketChannel.h"
#include "Core/Event/Loop/EventLoop.h"
#include "Core/String/Format/Format.h"
#include "Core/Network/Message/IMessage.h"

MEDUSA_BEGIN;

SocketChannel::SocketChannel(EventLoop* loop, const Socket& socket)
	:IEventChannel(loop),mSocket(socket)
{
	
}


SocketChannel::SocketChannel(EventLoop* loop)
	:IEventChannel(loop)
{

}

SocketChannel::~SocketChannel(void)
{
	
}


void SocketChannel::Reset()
{
	mSocket.SetSocketDescriptor(MedusaInvalidSocket);
}

void SocketChannel::OnRead()
{
	mLoop->AssertInLoopThread();

	auto socketError = mSocket.ReceiveAsync(mReadBuffer);
	if (socketError == ChannelEventResult::Success||socketError== ChannelEventResult::InProgress)
	{
		while (OnHandleRead());	//read all message
	}
	else
	{
		OnClose();
		return;
	}
}


void SocketChannel::OnWrite()
{
	//loop pipeline write 
	//write buffer to write
	if (mWriteBuffer.ReadableCount() > 0)
	{
		auto socketError = mSocket.SendAsync(mWriteBuffer);
		if (socketError == ChannelEventResult::Success)
		{
		}
		else if (socketError == ChannelEventResult::InProgress)
		{

		}
		else
		{
			OnError();
			return;
		}
	}
	
	if (mWriteBuffer.ReadableCount()<=0)
	{
		MEDUSA_FLAG_REMOVE(mCaredEvents, ChannelEventFlags::Write);
	}
}


void SocketChannel::OnError()
{
	IEventChannel::OnError();
	mSocket.Close();
}

void SocketChannel::OnClose()
{
	IEventChannel::OnClose();
	mSocket.ShutDown();
	mSocket.Close();
}

void SocketChannel::OnIdle()
{
	Close();	//close self
}


void SocketChannel::OnActive()
{

}

bool SocketChannel::OnHandleRead()
{
	//if (mReadHandler != nullptr)
	//{
	//	SocketConnectionEventHandlerContext context(*this);
	//	while (mReadHandler->Read(&context, any(&mReadBuffer)));	//process all data
	//}
	//else
	//{
	//	mReadBuffer.RetrieveAll();	//drop out all data
	//}
	//return true;
	mReadBuffer.RetrieveAll();	//drop out all data
	return false;
}


MEDUSA_END;
