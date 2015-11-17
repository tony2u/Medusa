// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenTraits.h"
#include "Core/Siren/SirenPropertyModifier.h"


MEDUSA_SIREN_BEGIN;

template<ushort TId, SirenPropertyModifier TModifier, typename TClass, typename TProperty, TProperty TClass::*TPropertyAddress, typename TKey = void, typename TValue = void>
class PropertyInfo	//[IGNORE_PRE_DECLARE]
{
public:
	typedef TClass ClassType;
	typedef TProperty PropertyType;
	typedef TProperty TClass::*PropertyAddressType;
	typedef typename SirenTraits<TProperty>::MetadataType MetadataType;
	typedef TKey KeyType;
	typedef TValue ValueType;


	const static bool IsList = !std::is_same<TKey, void>::value&&std::is_same<TValue, void>::value;
	const static bool IsDictionary = !std::is_same<TKey, void>::value&&!std::is_same<TValue, void>::value;
	const static bool IsNotContainer = std::is_same<TKey, void>::value&&std::is_same<TValue, void>::value;

	const static SirenPropertyModifier Modifier = (SirenPropertyModifier)TModifier;
	const static bool IsRequired = ((uint)TModifier&(uint)SirenPropertyModifier::Required) == (uint)SirenPropertyModifier::Required;

	const static ushort Id = TId;
	const static MetadataType Metadata;
public:
	PropertyInfo()
	{

	}
	~PropertyInfo(void)
	{

	}
public:
	static const TProperty& Get(const TClass& object) { return object.*TPropertyAddress; }
	static TProperty& Get(TClass& object) { return object.*TPropertyAddress; }

	static void SetToDefault(TClass& object)
	{
		Metadata.SetToDefault(Get(object));
	}

	static bool HasValue(const TClass& object)
	{
		return Metadata.HasValue(Get(object));
	}

};

MEDUSA_SIREN_END;
