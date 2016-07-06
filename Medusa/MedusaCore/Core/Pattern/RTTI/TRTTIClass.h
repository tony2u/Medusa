// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "RTTIClass.h"

MEDUSA_BEGIN;

template<typename T,typename TBase>
class TRTTIClass
{
public:
	constexpr TRTTIClass(const char* className)
		:mName(className)
	{

	}

	const RTTIClass& This()const
	{
		const static RTTIClass rtti(mName, typeid(T), &TBase::ClassStatic());
		return rtti;
	}
	
private:
	const char* mName;

};


MEDUSA_END;