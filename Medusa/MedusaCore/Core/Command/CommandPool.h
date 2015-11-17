// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "ICommand.h"
#include "Core/Pattern/RTTI/RTTIClass.h"
#include "Core/Pattern/Singleton.h"
MEDUSA_BEGIN;


class CommandPool :public MapObjectFactory<const RTTIClass*, ICommand*(), DefaultHashCoder<const RTTIClass*>, true>, public Singleton<CommandPool>
{
	friend class Singleton < CommandPool > ;
private:
	CommandPool();
	~CommandPool(void);
public:
	using MapObjectFactory<const RTTIClass*, ICommand*(), DefaultHashCoder<const RTTIClass*>, true>::Register;
	using MapObjectFactory<const RTTIClass*, ICommand*(), DefaultHashCoder<const RTTIClass*>, true>::Create;
	using MapObjectFactory<const RTTIClass*, ICommand*(), DefaultHashCoder<const RTTIClass*>, true>::Recycle;



	template<typename TDerived>
	void Register()
	{
		Register<TDerived>(&TDerived::RTTIClassStatic());
	}

	template<typename TDerived>
	TDerived* Create()
	{
		TDerived* obj=(TDerived*)Create(&TDerived::RTTIClassStatic());
		if (obj!=nullptr)
		{
			obj->Initialize();
		}
		return obj;
	}

	void Recycle(ICommand* obj)
	{
		if (obj!=nullptr)
		{
			obj->Uninitialize();
		}

		Recycle(&(obj->Class()), obj);
	}
};

MEDUSA_END;
