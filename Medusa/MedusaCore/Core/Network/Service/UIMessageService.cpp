// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "UIMessageService.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Network/Message/IMessage.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

UIMessageService::UIMessageService(const StringRef& options /*= StringRef::Empty*/)
	:IService(options)
{
	mId = (uint)StaticId;
}

UIMessageService::~UIMessageService()
{
}

bool UIMessageService::Submit(const ShareCommand& command)
{
	if (!command->IsA<IMessage>())
	{
		Log::AssertFailedFormat("UIMessageService:{} only accept message type.", mId);
		return false;
	}
	ScopedLock lock(mMessageMutex);
	ShareMessage message = command.Cast<ShareMessage>();
	mMessages.Add(message);

	return true;
}

void UIMessageService::Update(float dt)
{
	//on ui thread
	if (!mMessages.IsEmpty())
	{
		ScopedLock lock(mMessageMutex);
		//for (auto& message : mMessages)
		{
			//post to ui thread

			//if (command->IsMock())
			//{
			//
			//}
			//if (command->Id() == 0)
			//{
			//	//a response
			
			//}
			//else
			//{
		
			//}

			//if (command->IsMock())
			//{

			//}
		}
		mMessages.Clear();
	}

}


MEDUSA_END;
