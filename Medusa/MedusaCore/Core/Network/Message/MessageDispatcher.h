// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Network/Message/Service/ServiceType.h"

MEDUSA_BEGIN;

class MessageDispatcher :public Singleton<MessageDispatcher>, public IInitializable
{
	friend class Singleton<MessageDispatcher>;
	MessageDispatcher(void);
	~MessageDispatcher(void);
public:
	void ClearUp();

	void AddService(IService* service);
	void RemoveService(size_t id);
	void AddService(ServiceType serverType, size_t id, StringRef host, ushort port);

	virtual bool Initialize();
	virtual bool Uninitialize();

	void Start();
	void Stop();
	void Send(IMessage* message);
protected:
	Dictionary<size_t, IService*> mServices;
};

MEDUSA_END;
