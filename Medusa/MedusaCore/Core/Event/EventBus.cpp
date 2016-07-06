// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "EventBus.h"
#include "Core/Log/Log.h"
#include "Core/Event/Service/ServiceFactory.h"
#include "Core/Event/Service/IService.h"
#include "Core/Command/ICommand.h"

MEDUSA_BEGIN;

EventBus::EventBus(void)
{

}

EventBus::~EventBus(void)
{
	ClearUp();
}

bool EventBus::Initialize()
{
	return true;
}

bool EventBus::Uninitialize()
{
	Stop();
	ClearUp();
	return true;
}


void EventBus::ClearUp()
{
	/*for (auto& service : mServices)
	{

	}*/
}


bool EventBus::Register(IService* service)
{
	if (!mServices.TryAdd(service->Id(), service))
	{
		Log::AssertFailedFormat("Duplicate service by id {}", service->Id());
		return false;
	}
	return true;

}


void EventBus::Unregister(uint id)
{
	auto service = mServices.RemoveKeyOptional(id, nullptr);
	SAFE_DELETE(service);
}

void EventBus::Start()
{
	for (auto& item : mServices)
	{
		item.Value->Start();
	}

}

void EventBus::Stop()
{
	for (auto& item : mServices)
	{
		item.Value->Stop();
	}
}


bool EventBus::Send(const ShareCommand& command)
{
	auto service = mServices.GetOptional(command->ToService(), nullptr);
	if (service != nullptr)
	{
		service->Submit(command);
		return true;
	}
	else
	{
		Log::AssertFailedFormat("Invalid command service Id:{}", command->ToService());
		return false;
	}

}

bool EventBus::Send(StringRef serviceName, const ShareCommand& command)
{
	auto* service = FindService(serviceName);
	Log::AssertNotNullFormat(service, "Cannot find service:{}", serviceName);
	return service->Submit(command);
}

bool EventBus::Send(uint id, const ShareCommand& command)
{
	auto* service = FindService(id);
	Log::AssertNotNullFormat(service, "Cannot find service:{}", id);
	return service->Submit(command);
}

void EventBus::Update(float dt)
{
	for (auto& item : mServices)
	{
		item.Value->Update(dt);
	}

}

IService* EventBus::FindService(uint id) const
{
	return mServices.GetOptional(id, nullptr);
}

IService* EventBus::FindService(StringRef serviceName) const
{
	for (auto& item : mServices)
	{
		if (item.Value->ClassName() == serviceName)
		{
			return item.Value;
		}
	}

	return nullptr;
}

MEDUSA_END;
