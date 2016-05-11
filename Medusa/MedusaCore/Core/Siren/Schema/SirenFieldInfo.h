// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenTraits.h"
#include "Core/Siren/Schema/Field/SirenFieldModifier.h"


MEDUSA_BEGIN;

template<ushort TId, SirenFieldModifier TModifier, typename TClass, typename TField, TField TClass::*TFieldAddress, typename TKey = void, typename TValue = void>
class SirenFieldInfo	//[IGNORE_PRE_DECLARE]
{
public:
	typedef TClass ClassType;
	typedef TField FieldType;
	typedef TField TClass::*FieldAddressType;
	typedef typename SirenTraits<TField>::MetadataType MetadataType;
	typedef TKey KeyType;
	typedef TValue ValueType;


	const static bool IsList = !std::is_same<TKey, void>::value&&std::is_same<TValue, void>::value;
	const static bool IsDictionary = !std::is_same<TKey, void>::value&&!std::is_same<TValue, void>::value;
	const static bool IsNotContainer = std::is_same<TKey, void>::value&&std::is_same<TValue, void>::value;

	const static SirenFieldModifier Modifier = (SirenFieldModifier)TModifier;
	const static bool IsRequired = ((uint)TModifier&(uint)SirenFieldModifier::Required) == (uint)SirenFieldModifier::Required;

	const static ushort Id = TId;
	const static MetadataType Metadata;
public:
	SirenFieldInfo()
	{

	}
	~SirenFieldInfo(void)
	{

	}
public:
	static const TField& Get(const TClass& object) { return object.*TFieldAddress; }
	static TField& Get(TClass& object) { return object.*TFieldAddress; }

	static void SetToDefault(TClass& object)
	{
		Metadata.SetToDefault(Get(object));
	}

	static bool HasValue(const TClass& object)
	{
		return Metadata.HasValue(Get(object));
	}

};

MEDUSA_END;
