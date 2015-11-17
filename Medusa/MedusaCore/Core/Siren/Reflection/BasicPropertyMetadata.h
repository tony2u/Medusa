// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_SIREN_BEGIN;

template<typename TProperty>
class BasicPropertyMetadata
{
public:
	BasicPropertyMetadata(const char* name, uint length, const TProperty& val)
		:Name(name, length), Default(val)
	{

	}

	template<typename T2>
	BasicPropertyMetadata(const char* name, uint length, T2 val)
		: Name(name, length), Default((TProperty)val)
	{

	}

	void SetToDefault(TProperty& outVal)const
	{
		outVal = Default;
	}

	bool HasValue(const TProperty& val)const
	{
		return !Math::IsEqual(val, Default);
	}

	const StringRef Name;
	TProperty Default;
};

MEDUSA_SIREN_END;
