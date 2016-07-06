// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "SocketChannel.h"

MEDUSA_BEGIN;


class ConnectSocketChannel :public SocketChannel
{
public:
	constexpr static uint InitialRetryDelayMilliseconds = 500U;	//0.5s
	constexpr static uint MaxRetryDelayMilliseconds = 30000U;	//30s
public:
	ConnectSocketChannel(SocketPeer* client);
	virtual ~ConnectSocketChannel(void);

	bool Start();
	bool Stop();
	void Reset();
	void Retry();

	void Connect();
	void Disconnect();
public:
	Event<void(const Socket&)> OnConnectionEstablished;
	Event<void()> OnStartConnecting;

protected:
	virtual void OnWrite()override;
	virtual void OnError()override;
	virtual void OnRetry()override;


protected:
	SocketPeer* mClient = nullptr;
	std::atomic<ConnectionState> mState = ConnectionState::Disconnected;
	uint mRetryDelayMilliseconds = InitialRetryDelayMilliseconds;

	bool mNoDelay = false;	//enable no delay to speed up sending. or TCP will wait to combine small packets to a big packet to send
};

MEDUSA_END;
