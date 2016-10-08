// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "PropertySet.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/variant.h"
MEDUSA_BEGIN;



class VariantPropertySet :public PropertySet < HeapString, variant<bool, int, float, HeapString>>
{
public:
	using DataType = variant<bool,int, float, HeapString>;
public:
	using BaseType = PropertySet < HeapString, DataType>;
	using BaseType::RemoveKey;
	using BaseType::Get;
	using BaseType::Set;


	template<typename T>
	T GetOptionalT(const StringRef& key, const T& defaultVal)const
	{
		const DataType* val = this->TryGetByOtherKey(key, key.HashCode());
		if (val!=nullptr)
		{
			return val->get<T>();
		}

		return defaultVal;
	}

	template<typename T>
	T GetT(const StringRef& key)const
	{
		const DataType& val = this->Get(key);
		return val.get<T>();
	}

	StringRef GetString(const StringRef& key)const
	{
		const DataType* val = this->TryGetByOtherKey(key, key.HashCode());
		if (val != nullptr&&val->is<HeapString>())
		{
			const HeapString& str= val->get<HeapString>();
			return str;
		}
		return StringRef::Empty;
	}

	bool Has(const StringRef& key)const
	{
		return this->ContainsOtherKey(key, key.HashCode());
	}


	bool RemoveKey(const StringRef& key)
	{
		return this->RemoveOtherKey(key, key.HashCode());
	}

	
	template<typename T>
	void Set(const StringRef& key, const T& val)
	{
		//avoid: recursive on all control paths, function will cause runtime stack overflow
		PropertySet < HeapString, DataType>::Set(HeapString(key), DataType(val));
	}

	void Set(const StringRef& key, const StringRef& val)
	{
		//avoid: recursive on all control paths, function will cause runtime stack overflow
		PropertySet < HeapString, DataType>::Set(HeapString(key), DataType(HeapString(val)));
	}
};

MEDUSA_END;