// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "SocketPeer.h"
#include "Core/Pattern/Event.h"
#include "Core/Event/Poll/SelectPoller.h"
#include "Core/Network/Socket/Channel/ConnectSocketChannel.h"
#include "Core/Log/Log.h"
#include "Core/Event/Poll/PollerFactory.h"

MEDUSA_BEGIN;

template<typename TConnection>
class TTcpClient:public SocketPeer
{
public:
	using SelfType = TTcpClient<TConnection>;
	using DataType = typename TConnection::DataType;
public:
	using SocketPeer::SocketPeer;
	virtual bool IsClient()const override { return true; }

	virtual ~TTcpClient(void)
	{
		SAFE_DELETE(mConnector);
		if (mConnection != nullptr)
		{
			mConnection->Reset();	//connection use the same socket as connector,so we have to reset to avoid close socket twice
		}
		SAFE_DELETE(mConnection);
	}
	virtual bool Start()override
	{
		mLoop.AttachToCurrentThread();

		IPoller* poller = PollerFactory::Instance().Create(mPollerName, &mLoop);
		mLoop.SetPoller(poller);
		SAFE_DELETE(mConnector);
		mConnector = new ConnectSocketChannel(this);
		mConnector->OnStartConnecting += [this] {OnStartConnecting(*this); };
		mConnector->OnConnectionEstablished += Bind(&TTcpClient::OnConnectionEstablished, this);
		mConnector->BeginWrite();
		mConnector->SubmitToLoop();
		return mConnector->Start();
	}

	virtual bool Stop()override
	{
		if (mConnection != nullptr)
		{
			mConnection->Close();
		}
		bool val = mConnector->Stop();
		SAFE_DELETE(mConnector);
		return val;
	}
	virtual SocketChannel* Channel()override
	{
		return mConnector;
	}
	TConnection* Connection() const { return mConnection; }
	bool IsConnected()const { return mConnection != nullptr; }
	HeapString RemoteAddress()const
	{
		return mConnector->ToString();
	}
public:
	Event<void(SelfType&)> OnStartConnecting;
	Event<void(TConnection&)> OnConnected;
	Event<void(TConnection&)> OnDisconnected;
	Delegate<void(IEventChannel&)> OnActiveDelegate;


public:
	bool Write(const DataType& val)
	{
		if (mConnection!=nullptr)
		{
			return mConnection->Write(val);
		}
		return false;
	}
protected:
	void OnConnectionEstablished(const Socket& sock)
	{
		mLoop.AssertInLoopThread();
		//Log::FormatInfo("Connected: {}", sock.Address().ToString());

		mConnector->DetachFromLoop();
		//remove connect channel from poller

		mConnection = new TConnection(this, &mLoop, sock);
		mConnection->BeginRead();
		mConnection->OnCloseEvent += Bind(&TTcpClient::OnCloseConnection, this);
		mConnection->OnActiveEvent += OnActiveDelegate;

		mLoop.RunInLoop([this] {mConnection->SubmitToLoop(); });
		mConnector->Reset();
		OnConnected(*mConnection);
	}
	void OnCloseConnection(IEventChannel& conn)
	{
		mLoop.AssertInLoopThread();
		OnDisconnected((TConnection&)conn);

		//conn already detach from pool
		IEventChannel* p = &conn;
		mLoop.QueueInLoop([p,this] {delete p; mConnection = nullptr; });
		//auto retry connect
		if (mConnector != nullptr)
		{
			mConnector->Reset();
			mConnector->Retry();
		}
	}
protected:
	ConnectSocketChannel* mConnector=nullptr;
	TConnection* mConnection=nullptr;
	
};

MEDUSA_END;
