// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Message/Handler/IMessageHandler.h"

MEDUSA_BEGIN;

class MockMessageHandler:public IMessageHandler
{
public:
	MockMessageHandler(size_t id, StringRef hostName, ushort port, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey);
	virtual ~MockMessageHandler();
protected:
	IMessage* SendMessage(IMessage* message);

public:
	virtual void Process();
};
MEDUSA_END;
