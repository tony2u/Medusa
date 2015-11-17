// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "IPredicate.h"

MEDUSA_BEGIN;


class PredicateFactory :public Singleton < PredicateFactory >, public MapObjectFactory < StringRef, IPredicate*() >
{
	friend class Singleton < PredicateFactory > ;
	PredicateFactory();
	~PredicateFactory(void) {}
public:
	using MapObjectFactory<StringRef, IPredicate*()>::Register;
	using MapObjectFactory<StringRef, IPredicate*()>::Create;

	template < typename T >
	void Register()
	{
		Register<T>(T::ClassStatic().Name());
	}

	IPredicate* SmartCreate(StringRef name);

};

MEDUSA_END;
