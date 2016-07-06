// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Network/Socket/Channel/SocketChannel.h"
#include "Core/Pattern/AutoIncreaseId.h"
#include "Core/String/String.h"
#include "Core/Event/Loop/EventLoop.h"

MEDUSA_BEGIN;


template<typename T>
class TSocketConnection :public SocketChannel
{
public:
	using SelfType = TSocketConnection<T>;
	using DataType = T;
public:
	TSocketConnection(SocketPeer* peer, EventLoop* loop, const Socket& socket)
		: SocketChannel(loop, socket), mPeer(peer)
	{
		mSocket.EnableKeepAlive(true);
		mId = AutoIncreaseId<SelfType>::New();
	}
	virtual ~TSocketConnection()
	{
	}

	SocketPeer* Peer() const { return mPeer; }
	void SetPeer(SocketPeer* val) { mPeer = val; }
	virtual HeapString ToString()const { return String::Format("{} - {}", mId, mSocket.Address().ToString()); }
	uint Id() const { return mId; }

	bool Write(const T& val)
	{
		if (this->mLoop->IsInLoop())
		{
			return OnHandleWrite(val);
		}
		else
		{
			this->mLoop->QueueInLoop([this, val] {this->OnHandleWrite(val); });
			return true;
		}
	}

	Event<bool(SelfType& connection, NetworkBuffer& buffer)> OnBufferReadEvent;
	Event<bool(SelfType& connection, NetworkBuffer& buffer)> OnBufferWriteEvent;
public:
	virtual void SubmitToLoop()override
	{
		mState = ConnectionState::Connected;
		SocketChannel::SubmitToLoop();
	}
protected:
	virtual bool OnHandleRead()override
	{
		OnBufferReadEvent.Invoke(*this, mReadBuffer);
		return false;
	}

	virtual bool OnHandleWrite(const T& val)
	{
		OnBufferWriteEvent.Invoke(*this, mWriteBuffer);
		return false;
	}
protected:
	SocketPeer* mPeer = nullptr;	//parent
	ConnectionState mState = ConnectionState::Connecting;
	uint mId = 0;

};




MEDUSA_END;
