// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/Hash/IHasher.h"
#include "Core/Hash/HasherType.h"

MEDUSA_BEGIN;

class HasherFactory :public MapObjectFactory<HasherType, IHasher*(), DefaultHashCoder<HasherType>>
{
public:
	using MapObjectFactory<HasherType, IHasher*(), DefaultHashCoder<HasherType>>::Create;
private:
	HasherFactory();
	~HasherFactory(){}
public:
	static HasherFactory& Instance()
	{
		static HasherFactory factory;
		return factory;
	}
};

MEDUSA_END;
