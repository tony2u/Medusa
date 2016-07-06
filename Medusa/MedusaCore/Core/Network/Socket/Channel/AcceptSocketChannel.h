// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "SocketChannel.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;


class AcceptSocketChannel:public SocketChannel
{
public:
	AcceptSocketChannel(SocketPeer* server);
	virtual ~AcceptSocketChannel(void);

	void Start();
	void Stop();


	SocketPeer* Server() const { return mServer; }
	void SetServer(SocketPeer* val) { mServer = val; }
public:
	Event<void(const Socket&)> OnNewConnection;
	Event<void()> OnStartListening;

protected:
	virtual void OnRead()override;
protected:
	SocketPeer* mServer = nullptr;

};

MEDUSA_END;
