// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ServiceDefines.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Event/Service/IService.h"

MEDUSA_BEGIN;

class ServiceFactory :public MapObjectFactory<HeapString, IService*(const StringRef& options)>, public Singleton<ServiceFactory>
{
	ServiceFactory();
	~ServiceFactory() {}
	friend class Singleton<ServiceFactory>;
public:
	using BaseType = MapObjectFactory<HeapString, IService*(const StringRef& options)>;
	using BaseType::Create;
	using BaseType::Register;

	template<typename TDerived>
	void Register()
	{
		Register<TDerived>(TDerived::ClassNameStatic());
	}

	template<typename TDerived>
	TDerived* Create(const StringRef& options = StringRef::Empty)
	{
		return (TDerived*)BaseType::Create(TDerived::ClassNameStatic(), options);
	}
};

MEDUSA_END;
