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
	using BaseType = PropertySet < HeapString, HeapString>;
	using BaseType::RemoveKey;
	using BaseType::Get;
	using BaseType::Set;


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

	bool Has(const StringRef& key)const
	{
		return this->ContainsOtherKey(key, key.HashCode());
	}


	bool RemoveKey(const StringRef& key)
	{
		return this->RemoveOtherKey(key, key.HashCode());
	}

	StringRef Get(const StringRef& key)const
	{
		const HeapString& val= this->GetOptionalByOtherKey(key,key.HashCode(),StringRef::Empty);
		return val.ToString();
	}

	StringRef Get(const StringRef& key)
	{
		const HeapString& val = this->GetOptionalByOtherKey(key, key.HashCode(), StringRef::Empty);
		return val.ToString();
	}

	void Set(const StringRef& key, const StringRef& val)
	{
		//avoid: recursive on all control paths, function will cause runtime stack overflow
		PropertySet < HeapString, HeapString>::Set(HeapString(key), HeapString(val));	
	}

	bool ToBool(const StringRef& key,bool optional=false)const;

	bool Parse(const StringRef& str);

	bool GetList(const StringRef& key, List<HeapString>& outItems)const;

	HeapString ToString()const
	{
		HeapString result;
		for (auto& keyValue:*this)
		{
			result.AppendFormat("{}={},",keyValue.Key,keyValue.Value);
		}
		result.RemoveLast();	//remove last ,
		return result;
	}

	static StringRef GetDeclareType(const StringRef& val);
};

MEDUSA_END;