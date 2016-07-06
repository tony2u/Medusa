// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "IMessage.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Share.h"
MEDUSA_BEGIN;


class MessageFactory :public MapObjectFactory<uint, IMessage*()>, public Singleton<MessageFactory>
{
	MessageFactory();
	~MessageFactory(void);
	friend class Singleton < MessageFactory >;
public:
	using BaseType = MapObjectFactory<uint, IMessage*()>;
	using BaseType::Register;

	template<typename TDerived>
	void Register(const uint& id)
	{
		BaseType::Register<TDerived>(id);
		mMessageTypes.Add(id, &TDerived::ClassStatic());
	}

	Share<IMessage> Create(uint id)
	{
		IMessage* obj = BaseType::Create(id);
		if (obj != nullptr)
		{
			obj->SetId(id);
			obj->Initialize();
		}
		return obj;
	}

	StringRef GetName(uint id)const
	{
		auto rtti=mMessageTypes.GetOptional(id, nullptr);
		if (rtti!=nullptr)
		{
			return rtti->Name();
		}
		return StringRef::Empty;
	}
protected:
	Dictionary<uint, const RTTIClass*> mMessageTypes;
};

MEDUSA_END;
