// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MessageDispatcher.h"
#include "Core/Network/Message/Service/ServiceFactory.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


MessageDispatcher::MessageDispatcher(void)
{

}


MessageDispatcher::~MessageDispatcher(void)
{
	ClearUp();
}

bool MessageDispatcher::Initialize()
{
	return Socket::InitializeAPI();
}

bool MessageDispatcher::Uninitialize()
{
	Stop();
	ClearUp();
	return Socket::UninitializeAPI();
}

void MessageDispatcher::AddService(ServiceType serverType, size_t id, StringRef host, ushort port)
{
	RemoveService(id);
	IService* service = ServiceFactory::Instance().Create(serverType, id, host, port);
	AddService(service);
}

void MessageDispatcher::ClearUp()
{
	SAFE_DELETE_DICTIONARY_VALUE(mServices);
}


void MessageDispatcher::AddService(IService* service)
{
	if (mServices.ContainsKey(service->Id()))
	{
		Log::AssertFailedFormat("Duplicate service by id {}", service->Id());
	}

	mServices.Add(service->Id(), service);
}


void MessageDispatcher::RemoveService(size_t id)
{
	IService* service = mServices.RemoveKeyOptional(id, nullptr);
	if (service != nullptr)
	{
		service->Stop();
		SAFE_DELETE(service);
	}
}

void MessageDispatcher::Start()
{
	for (auto& item:mServices)
	{
		item.Value->Start();
	}

}

void MessageDispatcher::Stop()
{
	for (auto& item : mServices)
	{
		item.Value->Start();
	}
}


void MessageDispatcher::Send(IMessage* message)
{
	LOG_ASSERT_NOT_NULL(message);

	IService* service= mServices.GetOptional(message->ServiceId(),nullptr);
	if (service!=nullptr)
	{
		service->Submit(message);
	}
	else
	{
		Log::AssertFailedFormat("Invalid message service Id:{}", message->ServiceId());
	}

}


MEDUSA_END;
