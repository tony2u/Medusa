// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

template<typename TField>
class SirenBasicFieldMetadata
{
public:
	SirenBasicFieldMetadata(const char* name, uint length, const TField& val, bool hasDefault)
		:Name(name, length), Default(val), HasDefault(hasDefault)
	{

	}

	template<typename T2>
	SirenBasicFieldMetadata(const char* name, uint length, T2 val, bool hasDefault)
		: Name(name, length), Default((TField)val), HasDefault(hasDefault)
	{

	}

	void SetToDefault(TField& outVal)const
	{
		if (HasDefault)
		{
			outVal = Default;
		}
	}

	bool HasValue(const TField& val)const
	{
		if (HasDefault)
		{
			return !Math::IsEqual(val, Default);
		}
		return true;
	}

	const StringRef Name;
	TField Default;
	bool HasDefault = false;
};

MEDUSA_END;
