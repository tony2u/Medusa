// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "RTTIClass.h"

MEDUSA_BEGIN;

template<typename T>
class TRTTIClassRoot
{
public:
	constexpr TRTTIClassRoot(const char* className)
		:mName(className)
	{

	}

	const RTTIClass& This()const
	{
		const static RTTIClass rtti(mName, typeid(T), nullptr);
		return rtti;
	}

private:
	const char* mName;
};


MEDUSA_END;