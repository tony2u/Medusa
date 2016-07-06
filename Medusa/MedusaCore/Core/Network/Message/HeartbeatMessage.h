// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IMessage.h"

MEDUSA_BEGIN;

class HeartbeatMessage :public IMessage
{
	MEDUSA_DECLARE_MESSAGE(HeartbeatMessage,IMessage);
public:
	constexpr static int mStaticId = 0;
public:
	using IMessage::IMessage;
	~HeartbeatMessage(void);
	virtual uint StaticId()const override { return mStaticId; }
	virtual bool NeedResponse()const override { return false; }

	virtual bool OnRequest(MessageSocketConnection& connection)override;

};

MEDUSA_END;
