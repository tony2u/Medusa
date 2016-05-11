// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Queue.h"
#include "Core/Network/Message/IMessage.h"
#include "Core/String/HeapString.h"
#include "ServiceDefines.h"

MEDUSA_BEGIN;

class IService
{
public:
	IService(size_t id, StringRef host, ushort port);
	virtual ~IService();
public:
	virtual ServiceType Type()const = 0;
	size_t Id() const { return mId; }
	StringRef Host() const { return mHost; }
	ushort Port() const { return mPort; }

	virtual bool Start() { return true; }
	virtual void Stop() {}

	virtual void Submit(IMessage* message);

	bool IsEmpty()const { return mMessageQueue.IsEmpty(); }

protected:
	size_t mId;
	HeapString mHost;
	ushort mPort;
	Queue<IMessage*> mMessageQueue;

	ServiceState mState = ServiceState::None;
};



MEDUSA_END;
