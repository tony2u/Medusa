// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "IBrain.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

class BrainFactory :public Singleton < BrainFactory >, public MapObjectFactory < StringRef, IBrain*() >
{
	friend class Singleton < BrainFactory >;
	BrainFactory() {}
	~BrainFactory(void) {}
public:
	using MapObjectFactory<StringRef, IBrain*()>::Register;
	using MapObjectFactory<StringRef, IBrain*()>::Create;

	template < typename T >
	void Register()
	{
		Register<T>(T::ClassStatic().Name());
	}

	IBrain* SmartCreate(StringRef name);

};

MEDUSA_END;
