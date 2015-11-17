// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "IBehavior.h"



MEDUSA_BEGIN;

class BehaviorFactory :public Singleton < BehaviorFactory >, public MapObjectFactory < StringRef, IBehavior*() >
{
	friend class Singleton < BehaviorFactory > ;

	BehaviorFactory();

	~BehaviorFactory(void) {}
public:
	using MapObjectFactory<StringRef, IBehavior*()>::Register;
	using MapObjectFactory<StringRef, IBehavior*()>::Create;

	template < typename T >
	void Register()
	{
		Register<T>(T::ClassStatic().Name());
	}

	IBehavior* SmartCreate(StringRef name);
};

MEDUSA_END;
