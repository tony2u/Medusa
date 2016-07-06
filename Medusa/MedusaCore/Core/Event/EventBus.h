// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Event/Service/ServiceDefines.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;


class EventBus :public Singleton<EventBus>, public IInitializable
{
	friend class Singleton<EventBus>;
	EventBus(void);
	~EventBus(void);
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
	void ClearUp();
	IService* FindService(StringRef serviceName)const;
	IService* FindService(uint id)const;

	bool Register(IService* service);
	void Unregister(uint id);

	template<typename T>
	T* Register(const StringRef& options = StringRef::Empty, uint customServiceId = Math::UIntMaxValue)
	{
		T* service = new T(options);
		service->SetId(customServiceId);
		Register(service);
		return service;
	}

	void Start();
	void Stop();
	void Update(float dt);

	bool Send(const ShareCommand& command);
	bool Send(StringRef serviceName, const ShareCommand& command);
	bool Send(uint id, const ShareCommand& command);

	template<typename T>
	bool Send(const ShareCommand& command)
	{
		return Send((uint)T::StaticId, command);
	}

private:
	Dictionary<uint, IService*> mServices;	//id-service
};

MEDUSA_END;
