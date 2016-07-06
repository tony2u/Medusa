// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Event/Service/IThreadService.h"
#include "Core/Network/Socket/TTcpServer.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Log/Log.h"
#include "Core/Event/Poll/SelectPoller.h"
MEDUSA_BEGIN;

template<typename TConnection>
class TTcpServerMessageService:public IThreadService
{
public:
	using ServerType = TTcpServer<TConnection>;
public:
	constexpr static ServiceIds StaticId = ServiceIds::TcpServer;
public:
	TTcpServerMessageService(const StringRef& options = StringRef::Empty)
		:IThreadService(options)
	{
		mId = (uint)StaticId;

		mServer.SetProperties(mProperties);
	}
	virtual ~TTcpServerMessageService() = default;
	virtual bool Submit(const ShareCommand& command)override
	{
		if (!command->IsA<IMessage>())
		{
			Log::AssertFailedFormat("TcpServerMessageService:{} only accept message type.", mId);
			return false;
		}

		//TODO: check connection id
		ShareMessage message = command.Cast<ShareMessage>();
		uint connectionId = message->ConnectionId();

		if (!mServer.Write(connectionId, message))
		{
			Log::AssertFailedFormat("TcpServerMessageService:{} Cannot find message connection:{}", mId, connectionId);
			return false;
		}
		return true;
	}
	ServerType& Server() { return mServer; }

	virtual void SetProperties(const StringPropertySet& val)override
	{
		IService::SetProperties(val);
		mServer.SetProperties(val);
	}
	virtual void AddAttribute(const StringRef& name, const StringRef& val)override
	{
		IService::AddAttribute(name, val);
		mServer.AddAttribute(name, val);
	}
protected:
	virtual bool OnStart()override
	{
		return mServer.Start();
	}
	virtual bool OnRunOnce(Thread& thread)override
	{
		return mServer.LoopOnce();
	}
	virtual bool OnStop()override
	{
		return mServer.Stop();
	}

protected:
	ServerType mServer;
};


MEDUSA_END;
