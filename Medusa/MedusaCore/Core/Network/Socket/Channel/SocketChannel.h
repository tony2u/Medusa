// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Event/Channel/IEventChannel.h"
#include "Core/Network/Socket/Socket.h"

MEDUSA_BEGIN;


class SocketChannel :public IEventChannel
{
public:
	SocketChannel(EventLoop* loop, const Socket& socket);
	SocketChannel(EventLoop* loop);
	virtual ~SocketChannel(void);

	virtual MedusaFileDescriptor EventHandle() const override { return mSocket.SocketDescriptor(); }

	void Reset();
	HeapString Address()const{ return mSocket.Address().IPString(); }
	ushort Port()const{ return mSocket.Address().Port(); }

	virtual HeapString ToString()const{ return mSocket.Address().ToString(); }

protected:
	virtual void OnRead()override;
	virtual void OnWrite()override;
	virtual void OnError()override;
	virtual void OnClose()override;
	virtual void OnIdle()override;
	virtual void OnActive()override;
	virtual bool OnHandleRead();


protected:
	Socket mSocket;
};

MEDUSA_END;
