// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "AcceptSocketChannel.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/Log/Log.h"
#include "Core/Network/Socket/SocketPeer.h"

MEDUSA_BEGIN;

AcceptSocketChannel::AcceptSocketChannel(SocketPeer* server)
	:mServer(server),
	SocketChannel(&server->MutableLoop())
{
	const auto& properties = mServer->Properties();

	IPAddress address(mServer->Host(), mServer->Port());
	IPProtocol protocol = IPProtocol::GetProtocol(SocketProtocolType::TCP);
	mSocket.SetAddress(address);
	mSocket.SetProtocol(protocol);

	mSocket.CreateSocket();

	bool resusePort = properties.GetOptionalT("ReusePort", true);
	bool resuseAddress = properties.GetOptionalT("ReuseAddress", true);
	bool noDelay = properties.GetOptionalT("NoDelay", false);

	mSocket.EnableReusePort(resusePort);
	mSocket.EnableReuseAddress(resuseAddress);
	mSocket.EnableTcpNoDelay(noDelay);
	mSocket.EnableAsync(true);
	mSocket.Bind();
}

AcceptSocketChannel::~AcceptSocketChannel(void)
{
	mSocket.Close();
}

void AcceptSocketChannel::Start()
{
	mSocket.Listen();
	BeginRead();
	OnStartListening();
}


void AcceptSocketChannel::Stop()
{
	//stop listening
}

void AcceptSocketChannel::OnRead()
{
	//new connection
	Socket outSocket;
	bool isSuccess= mSocket.Accept(outSocket);
	outSocket.SetSendBufferSize(1024 * 128);
	outSocket.SetReceiveBufferSize(1024 * 128);


	if (isSuccess)
	{
		if (!OnNewConnection.IsEmpty())
		{
			OnNewConnection(outSocket);
		}
		else
		{
			outSocket.Close();
		}
	}
	else
	{
		//TODO: accept failed
	}
}

MEDUSA_END;