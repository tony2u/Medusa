// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "TcpClientService.h"
#include "Core/Log/Log.h"
#include "Core/Network/Socket/AddressInfo.h"
#include "Core/Network/Socket/ProtocolInfo.h"
#include "Core/Network/Message/MessageFactory.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Threading/Thread.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Profile/AutoStopWatch.h"
#include "Core/Threading/ScopedLock.h"


MEDUSA_BEGIN;

TcpClientService::TcpClientService(size_t id, StringRef host, ushort port)
	:BaseSocketService(id, host, port)
{
	mSocket.EnableAsync(true);
}

TcpClientService::~TcpClientService()
{
}

void TcpClientService::OnStart()
{
	//try to connect
	for (uint i = 0; i < 5; ++i)	//retry times
	{
		SocketError connectResult = mSocket.ConnectAsync(100);	//timeout
		if (connectResult == SocketError::Success)
		{
			mState = ServiceState::Running;
			return;
		}
		else if (connectResult == SocketError::Fault)	//socket error
		{
			mState = ServiceState::Failed;
			mSocket.Close();
			//raise failed event
			return;
		}
		//timeout
	}

	//still failed at last
	mState = ServiceState::Failed;
	mSocket.Close();
}

void TcpClientService::OnRun()
{
	SocketEventFlags outFlags;
	SocketError selectResult = mSocket.Select(outFlags, SocketEventFlags::ReadWrite);
	if (selectResult == SocketError::Fault)
	{
		mState = ServiceState::Failed;
		//raise failed event
		return;
	}

	if (MEDUSA_FLAG_HAS(outFlags, SocketEventFlags::Read))
	{
		//read to buffer
		//loop to pipeline read
	}

	if (MEDUSA_FLAG_HAS(outFlags, SocketEventFlags::Write))
	{
		//loop pipeline write 
		//write buffer to write
	}

}



MEDUSA_END;
