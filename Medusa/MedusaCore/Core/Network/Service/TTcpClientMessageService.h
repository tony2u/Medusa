// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Event/Service/IThreadService.h"
#include "Core/Network/Socket/TTcpClient.h"
#include "Core/Chrono/StopWatch.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Log/Log.h"
#include "Core/Event/Poll/SelectPoller.h"
#include "Core/Event/EventBus.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/Event/Service/ServiceDefines.h"
#include "Core/Network/Message/HeartbeatMessage.h"

MEDUSA_BEGIN;

template<typename TConnection>
class TTcpClientMessageService :public IThreadService
{
public:
	using ClientType = TTcpClient<TConnection>;

	constexpr static ServiceIds StaticId = ServiceIds::TcpClient;
public:
	TTcpClientMessageService(const StringRef& options = StringRef::Empty)
		:IThreadService(options)
	{
		mId = (uint)StaticId;

		mClient.SetProperties(mProperties);
		mClient.OnActiveDelegate = Bind(&TTcpClientMessageService::OnActive, this);
		mHeartbeatMilliseconds = mProperties.GetOptionalT(ServicePropertyNames::HeartbeatMilliseconds, 0);
	}

	virtual ~TTcpClientMessageService() = default;
	virtual bool Submit(const ShareCommand& command)override
	{
		if (!command->IsA<IMessage>())
		{
			Log::AssertFailedFormat("TcpClientMessageService:{} only accept message type.", mId);
			return false;
		}

		auto con = mClient.Connection();
		if (con == nullptr)
		{
			Log::AssertFailedFormat("TcpClientMessageService:{} only accept message after connected.", mId);
			return false;
		}

		ShareMessage message = command.Cast<ShareMessage>();
		return con->Write(message);
	}
	ClientType& Client() { return mClient; }

	virtual void SetProperties(const StringPropertySet& val)override
	{
		IService::SetProperties(val);
		mClient.SetProperties(val);
	}
	virtual void AddAttribute(const StringRef& name, const StringRef& val)override
	{
		IService::AddAttribute(name, val);
		mClient.AddAttribute(name, val);
	}
protected:
	virtual bool OnStart()override
	{
		mHeartbeatWatch.Start();
		return mClient.Start();
	}
	virtual bool OnRunOnce(Thread& thread)override
	{
		bool isSuccess = mClient.LoopOnce();
		if (mHeartbeatMilliseconds != 0 && mClient.IsConnected())
		{
			mHeartbeatWatch.Shot();
			if (mHeartbeatWatch.ElapsedMilliseconds() >= (float)mHeartbeatMilliseconds)
			{
				mHeartbeatWatch.Step();
				Share<HeartbeatMessage> message = new HeartbeatMessage();
				mClient.Write(message);
			}
		}

		return isSuccess;
	}
	virtual bool OnStop()override
	{
		return mClient.Stop();
	}
	void OnActive(IEventChannel&)
	{
		if (mHeartbeatMilliseconds != 0)
		{
			mHeartbeatWatch.Step();//reset heartbeat watch
		}
	}

protected:
	ClientType mClient;
	uint mHeartbeatMilliseconds = 0;
	StopWatch mHeartbeatWatch;

};
MEDUSA_END;
