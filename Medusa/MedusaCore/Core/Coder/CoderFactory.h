// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/Coder/ICoder.h"
#include "Core/Coder/CoderType.h"

MEDUSA_BEGIN;

class CoderFactory :public MapObjectFactory<CoderType, ICoder*(const IEventArg&), DefaultHashCoder<CoderType>>
{
public:
	using MapObjectFactory<CoderType, ICoder*(const IEventArg&), DefaultHashCoder<CoderType>>::Create;
private:
	CoderFactory();
	~CoderFactory(){}
public:
	static CoderFactory& Instance()
	{
		static CoderFactory factory;
		return factory;
	}

	static CoderType ParseCoderType(const StringRef& str);
	static bool RequireKey(CoderType coderType);

};

MEDUSA_END;
