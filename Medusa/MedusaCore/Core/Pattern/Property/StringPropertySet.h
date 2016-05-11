// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "PropertySet.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;

class StringPropertySet :public PropertySet < HeapString, HeapString>
{
public:
	template<typename T>
	T GetOptionalT(const StringRef& key, const T& defaultVal)const
	{
		auto val = this->GetOptionalByOtherKey(key, key.HashCode(), StringRef::Empty);
		if (val.IsEmpty())
		{
			return defaultVal;
		}
		return StringParser::StringTo<T>(val);
	}

	template<typename T>
	T GetT(const StringRef& key)const
	{
		auto val = this->Get(key);
		return StringParser::StringTo<T>(val);
	}


	StringRef Get(const StringRef& key)const
	{
		const HeapString& val= this->GetOptionalByOtherKey(key,key.HashCode(),StringRef::Empty);
		return val.ToString();
	}

	void Set(const StringRef& key, const StringRef& val)
	{
		//avoid: recursive on all control paths, function will cause runtime stack overflow
		PropertySet < HeapString, HeapString>::Set(HeapString(key), HeapString(val));	
	}
};

MEDUSA_END;