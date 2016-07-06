// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "IState.h"



MEDUSA_BEGIN;

class StateFactory : public MapObjectFactory < StringRef, IState*() >, public Singleton < StateFactory >
{
	friend class Singleton < StateFactory >;
	StateFactory();
	~StateFactory(void) {}
public:
	using MapObjectFactory<StringRef, IState*()>::Register;
	using MapObjectFactory<StringRef, IState*()>::Create;

	template < typename T >
	void Register()
	{
		Register<T>(T::ClassStatic().Name());
	}

	IState* SmartCreate(StringRef name);

};

MEDUSA_END;
