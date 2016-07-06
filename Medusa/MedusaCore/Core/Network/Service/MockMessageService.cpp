// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MockMessageService.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Network/Message/IMessage.h"
#include "Core/Event/EventBus.h"
#include "Core/Log/Log.h"
#include "Core/Network/Service/UIMessageService.h"

MEDUSA_BEGIN;

MockMessageService::MockMessageService(const StringRef& options /*= StringRef::Empty*/)
	:IThreadService(options)
{
	mId = (uint)StaticId;
}

MockMessageService::~MockMessageService()
{
	mMessageSessions.Clear();
}

bool MockMessageService::Submit(const ShareCommand& command)
{
	if (!command->IsA<IMessage>())
	{
		Log::AssertFailedFormat("MockMessageService:{} only accept message type.", mId);
		return false;
	}
	ScopedLock lock(mMessageMutex);
	ShareMessage message = command.Cast<ShareMessage>();
	mMessageSessions.Add(message->SessionId(), message);

	return true;
}

bool MockMessageService::OnRunOnce(Thread& thread)
{
	ScopedLock lock(mMessageMutex);
	if (!mMessageSessions.IsEmpty())
	{
		for (auto& item: mMessageSessions)
		{
			auto message = item.Value;
			//invoke OnRequest
			//encode response
			if (message->Id() == 0)	//a response
			{
				//Math::Swap(message->MutableResponseData(), message->MutableRequestData());
				Math::Swap(message->MutableFromService(), message->MutableToService());	//send back
			}
			else
			{
				//a request
			}
			

			//message->SetServiceId(); to main
			EventBus::Instance().Send(message);
		}
		mMessageSessions.Clear();
	}
	return true;
}


MEDUSA_END;
