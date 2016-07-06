// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Network/Socket/TSocketConnection.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Network/Message/IMessage.h"

MEDUSA_BEGIN;


class MessageSocketConnection :public TSocketConnection<ShareMessage>
{
public:
	using DataType = ShareMessage;
	using BaseType = TSocketConnection<ShareMessage>;
public:
	MessageSocketConnection(SocketPeer* peer, EventLoop* loop, const Socket& socket);

	virtual ~MessageSocketConnection(void);
protected:
	virtual bool OnHandleRead()override;
	virtual bool OnHandleWrite(const ShareMessage& val) override;
public:
	ShareMessage TryRemoveSession(uint sessionId);
protected:
	Dictionary<size_t, ShareMessage> mMessageSessions;
	uint mCurrentSessionId = 0;

};

MEDUSA_END;
