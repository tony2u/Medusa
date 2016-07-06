// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/Pattern/Singleton.h"
#include "IPoller.h"

MEDUSA_BEGIN;

class PollerFactory :public MapObjectFactory<HeapString, IPoller*(EventLoop* loop)>, public Singleton<PollerFactory>
{
	PollerFactory();
	~PollerFactory() {}
	friend class Singleton<PollerFactory>;
public:
	using BaseType = MapObjectFactory<HeapString, IPoller*(EventLoop* loop)>;
	using BaseType::Create;
	using BaseType::Register;

	template<typename TDerived>
	void Register()
	{
		Register<TDerived>(TDerived::ClassNameStatic());
	}

	template<typename TDerived>
	TDerived* Create(EventLoop* loop=nullptr)
	{
		return (TDerived*)BaseType::Create(TDerived::ClassNameStatic(), loop);
	}
};

MEDUSA_END;
