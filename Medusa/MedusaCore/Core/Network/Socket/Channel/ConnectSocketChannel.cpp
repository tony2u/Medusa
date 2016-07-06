// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ConnectSocketChannel.h"
#include "Core/Math/Math.h"
#include "Core/Log/Log.h"
#include "Core/Network/Socket/SocketPeer.h"

MEDUSA_BEGIN;

ConnectSocketChannel::ConnectSocketChannel(SocketPeer* client)
	:SocketChannel(&client->MutableLoop()), mClient(client)
{
	const auto& properties = mClient->Properties();

	mNoDelay = properties.GetOptionalT("NoDelay", false);

	IPAddress address(mClient->Host(), mClient->Port());
	IPProtocol protocol = IPProtocol::GetProtocol(SocketProtocolType::TCP);
	mSocket.SetAddress(address);
	mSocket.SetProtocol(protocol);
	mSocket.SetSendBufferSize(1024 * 128);
	mSocket.SetReceiveBufferSize(1024 * 128);
}

ConnectSocketChannel::~ConnectSocketChannel(void)
{
	mSocket.Close();
}

bool ConnectSocketChannel::Start()
{
	OnStartConnecting();
	if (mLoop->IsInLoop())
	{
		Connect();
	}
	else
	{
		mLoop->RunInLoop([this] {Connect(); });
	}
	return true;
}

bool ConnectSocketChannel::Stop()
{
	switch (mState)
	{
	case ConnectionState::Connected:
		mSocket.ShutDown(ChannelPipeType::ReadWrite);
		mState = ConnectionState::Disconnecting;
		break;
	case ConnectionState::Connecting:
		mState = ConnectionState::Disconnecting;
		break;
	default:
		break;
	}
	return true;
}


void ConnectSocketChannel::Reset()
{
	mRetryDelayMilliseconds = InitialRetryDelayMilliseconds;
}

void ConnectSocketChannel::Connect()
{
	RETURN_IF_EQUAL(mState, ConnectionState::Connected);
	mState = ConnectionState::Connecting;
	mLoop->AssertInLoopThread();
	mSocket.CreateSocket();
	mSocket.EnableAsync(true);
	mSocket.EnableTcpNoDelay(true);

	ChannelEventResult connectResult = mSocket.Connect();	//connect timeout
	switch (connectResult)
	{
	case ChannelEventResult::Success:
		mState = ConnectionState::Connected;
		return;
	case ChannelEventResult::InProgress:
		mState = ConnectionState::Connecting;
		BeginWrite();
		SubmitToLoop();
		break;
	case ChannelEventResult::Retry:
		Retry();
		break;
	case ChannelEventResult::Fault:
	default:
		OnError();
		break;
	}

}

void ConnectSocketChannel::Disconnect()
{
	//called by tcp client
	mSocket.Close();
	mState = ConnectionState::Disconnected;
	DetachFromLoop();
}

void ConnectSocketChannel::Retry()
{


	mSocket.Close();
	mState = ConnectionState::Disconnected;

	DetachFromLoop();
	//retry at next delay
	Log::FormatInfo("Retry:{}", mRetryDelayMilliseconds);

	mLoop->RunAfter([this]() {Connect(); }, mRetryDelayMilliseconds);
	mRetryDelayMilliseconds = Math::Min(mRetryDelayMilliseconds * 2, MaxRetryDelayMilliseconds);

	//Connect();
}

void ConnectSocketChannel::OnWrite()
{

	if (mState == ConnectionState::Connecting)
	{
		int err = mSocket.GetError();
		if (err != 0)
		{
			Log::FormatError("Connect error:{}", err);
			Retry();
		}
		else if (mSocket.IsSelfConnected())
		{
			Log::FormatError("Self connect.");
			Retry();
		}
		else
		{
			mState = ConnectionState::Connected;
			OnConnectionEstablished(mSocket);
		}
	}
	else
	{
		//error
	}
}


void ConnectSocketChannel::OnError()
{
	SocketChannel::OnError();
	if (mState == ConnectionState::Connecting)
	{
		Retry();
	}
}

void ConnectSocketChannel::OnRetry()
{
	//SocketChannel::OnRetry();

	if (mState == ConnectionState::Connecting)
	{
		Retry();
	}
}

MEDUSA_END;

