// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/HashSet.h"
#include "Core/Event/Loop/EventLoopThreadPool.h"
#include "SocketPeer.h"
#include "Core/Pattern/Event.h"
#include "Core/Threading/Mutex.h"
#include "Core/Network/Socket/Channel/AcceptSocketChannel.h"
#include "Core/System/Environment.h"
#include "Core/Log/Log.h"
#include "Core/Event/Poll/PollerFactory.h"
#include "Core/Event/Service/ServiceDefines.h"
MEDUSA_BEGIN;

template<typename TConnection>
class TTcpServer :public SocketPeer
{
public:
	using SelfType = TTcpServer<TConnection>;
	using DataType =typename TConnection::DataType;
public:
	using SocketPeer::SocketPeer;
	virtual bool IsClient()const override { return false; }

	virtual ~TTcpServer(void)
	{
		SAFE_DELETE(mAcceptor);
		SAFE_DELETE_DICTIONARY_VALUE(mConnections);
	}
	Mutex& MutableConnectionMutex() { return mConnectionMutex; }


	virtual bool Start()override
	{
		mLoop.AttachToCurrentThread();

		mIdleMilliseconds = mProperties.GetOptionalT(ServicePropertyNames::IdleMilliseconds, 0);

		IPoller* poller = PollerFactory::Instance().Create(mPollerName, &mLoop);
		mLoop.SetPoller(poller);
		mAcceptor = new AcceptSocketChannel(this);
		mAcceptor->OnNewConnection += Bind(&TTcpServer::OnAcceptConnection, this);
		mAcceptor->OnStartListening += [this] {OnStartListening(*this); };

		mAcceptor->SubmitToLoop();

		int threadCount = mProperties.GetOptionalT(ServicePropertyNames::ThreadCount, Environment::Instance().CPUCount() * 2);
		mThreadPool.Start(threadCount, mPollerName);
		mAcceptor->Start();
		return true;
	}
	virtual bool Stop() override
	{
		mThreadPool.Stop();
		SAFE_DELETE(mAcceptor);
		SAFE_DELETE_DICTIONARY_VALUE(mConnections);
		return true;
	}

	virtual SocketChannel* Channel()override
	{
		return mAcceptor;
	}
	TConnection* FindConnection(uint id)const
	{
		ScopedLock lock(mConnectionMutex);
		return mConnections.GetOptional(id, nullptr);
	}

	bool Write(uint connectionId, const DataType& val)
	{
		ScopedLock lock(mConnectionMutex);
		auto* connection = mConnections.GetOptional(connectionId, nullptr);
		RETURN_FALSE_IF_NULL(connection);
		return connection->Write(val);
	}

	bool Broadcast(const DataType& val)
	{
		ScopedLock lock(mConnectionMutex);
		for (auto i : mConnections)
		{
			auto connection = i.Value;
			conn->Write(val);
		}
		return true;
	}

	
	bool Broadcast(uint fromConnectionId, const DataType& val)
	{
		ScopedLock lock(mConnectionMutex);
		for (auto i : mConnections)
		{
			if (i.Key != fromConnectionId)
			{
				auto connection = i.Value;
				connection->Write(val);
			}

		}
		return true;
	}

	bool CloseConnection(uint id)
	{
		val->Close();
		//will fire OnCloseConnection later
		return true;
	}
	bool CloseConnection(TConnection* val)
	{
		auto conn = FindConnection(id);
		RETURN_FALSE_IF_NULL(conn);
		return CloseConnection(conn);
	}

public:
	Event<void(TConnection&)> OnNewConnection;
	Event<void(TConnection&)> OnConnectionClose;
	Event<void(SelfType&)> OnStartListening;
protected:
	void OnAcceptConnection(const Socket& sock)
	{
		mLoop.AssertInLoopThread();
		ScopedLock lock(mConnectionMutex);

		EventLoop* nextLoop = mThreadPool.NextLoop();

		TConnection* conn = new TConnection(this, nextLoop, sock);
		conn->SetIdleMilliseconds(mIdleMilliseconds);
		conn->BeginRead();
		conn->OnCloseEvent += [this](IEventChannel& conn2) {mLoop.RunInLoop([this, &conn2]() {OnCloseConnection(conn2); }); };	//post to main event loop


		mConnections.Add(conn->Id(), conn);
		nextLoop->RunInLoop([conn] {conn->SubmitToLoop(); });

		OnNewConnection(*conn);
	}
	void OnCloseConnection(IEventChannel& conn)
	{
		mLoop.AssertInLoopThread();

		auto& socketConnection = (TConnection&)conn;
		OnConnectionClose(socketConnection);

		//conn already detach from pool
		mConnections.RemoveKey(socketConnection.Id());
		IEventChannel* p = &conn;
		mLoop.QueueInLoop([p] {delete p; });
	}
protected:
	AcceptSocketChannel* mAcceptor = nullptr;	//use ptr to polymorphic one day
	EventLoopThreadPool mThreadPool;

	Dictionary<uint, TConnection*> mConnections;	//id
	mutable Mutex mConnectionMutex;

	uint mIdleMilliseconds;
};

MEDUSA_END;
