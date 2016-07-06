// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Event/Service/IThreadService.h"
#include "Core/Threading/Mutex.h"
#include "Core/Network/Message/IMessage.h"
MEDUSA_BEGIN;

class MockMessageService:public IThreadService
{
	MEDUSA_RTTI(MockMessageService,IThreadService);
public:
	constexpr static ServiceIds StaticId = ServiceIds::MockMessage;
public:
	MockMessageService(const StringRef& options = StringRef::Empty);
	virtual ~MockMessageService();


	virtual bool Submit(const ShareCommand& command)override;

protected:
	virtual bool OnRunOnce(Thread& thread)override;
protected:
	Dictionary<size_t, ShareMessage> mMessageSessions;
	Mutex mMessageMutex;
};
MEDUSA_END;
