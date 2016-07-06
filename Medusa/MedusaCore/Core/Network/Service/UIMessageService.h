// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Event/Service/IService.h"
#include "Core/Threading/Mutex.h"
#include "Core/Collection/List.h"
#include "Core/Network/Message/IMessage.h"
MEDUSA_BEGIN;

class UIMessageService:public IService
{
	MEDUSA_RTTI(UIMessageService,IService);
public:
	constexpr static ServiceIds StaticId = ServiceIds::UIMessage;
public:
	UIMessageService(const StringRef& options = StringRef::Empty);
	virtual ~UIMessageService();
	virtual bool Submit(const ShareCommand& command)override;
	virtual void Update(float dt)override;

protected:
	List<ShareMessage> mMessages;
	Mutex mMessageMutex;
};
MEDUSA_END;
