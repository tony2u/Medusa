// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "TTcpServerMessageService.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Log/Log.h"
#include "Core/Network/Message/Connection/MessageSocketConnection.h"
#include "Core/Event/Poll/SelectPoller.h"

MEDUSA_BEGIN;

TTcpServerMessageService::TTcpServerMessageService(const StringRef& options /*= StringRef::Empty*/)
	:IThreadService(options)
{
	mId = (uint)StaticId;

	mServer.SetProperties(mProperties);
}

TTcpServerMessageService::~TTcpServerMessageService()
{

}

bool TTcpServerMessageService::Submit(const ShareCommand& command)
{
	
}

void TTcpServerMessageService::AddAttribute(const StringRef& name, const StringRef& val)
{
	
}

void TTcpServerMessageService::SetProperties(const StringPropertySet& val)
{
	
}

bool TTcpServerMessageService::OnStart()
{
}

bool TTcpServerMessageService::OnRunOnce(Thread& thread)
{
}

bool TTcpServerMessageService::OnStop()
{
}

MEDUSA_END;
