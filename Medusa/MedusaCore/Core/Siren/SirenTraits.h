// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "SirenMacro.h"
#include "Core/Siren/Schema/SirenBasicFieldMetadata.h"
#include "Core/Siren/Schema/SirenStructFieldMetadata.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"
#include "Core/Siren/SirenDefines.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;
namespace Siren
{

	template <typename T, typename Enable = void>
	struct GetSchema;

	template <typename T>
	struct GetSchema < T, typename std::enable_if<std::is_class<typename T::Schema::Fields>::value>::type >
	{
		typedef typename T::Schema Type;
	};


	template <typename T, typename Enable = void>
	struct HasSchema : std::false_type {};

	template <typename T>
	struct HasSchema<T, typename std::enable_if<std::is_class<typename GetSchema<T>::Type>::value>::type> : std::true_type {};


	template <typename T, typename Enable = void>
	struct HasBaseType :std::false_type {};

	template <typename T>
	struct HasBaseType<T, typename std::enable_if<!std::is_same<typename T::BaseType, void>::value>::type> : std::true_type {};

	template <typename T>
	struct GetDataType { const static byte Type = (byte)SirenTypeId::Struct.IntValue; };
	template <>
	struct GetDataType < bool > { const static byte Type = (byte)SirenTypeId::Bool.IntValue; };
	template <>
	struct GetDataType < char > { const static byte Type = (byte)SirenTypeId::Int8.IntValue; };
	template <>
	struct GetDataType < byte > { const static byte Type = (byte)SirenTypeId::UInt8.IntValue; };
	template <>
	struct GetDataType < short > { const static byte Type = (byte)SirenTypeId::Int16.IntValue; };
	template <>
	struct GetDataType < ushort > { const static byte Type = (byte)SirenTypeId::UInt16.IntValue; };
	template <>
	struct GetDataType < int > { const static byte Type = (byte)SirenTypeId::Int32.IntValue; };
	template <>
	struct GetDataType < uint > { const static byte Type = (byte)SirenTypeId::UInt32.IntValue; };
	template <>
	struct GetDataType < int64 > { const static byte Type = (byte)SirenTypeId::Int64.IntValue; };
	template <>
	struct GetDataType < uint64 > { const static byte Type = (byte)SirenTypeId::UInt64.IntValue; };
	template <>
	struct GetDataType < HeapString > { const static byte Type = (byte)SirenTypeId::String.IntValue; };
	template <>
	struct GetDataType < Blob > { const static byte Type = (byte)SirenTypeId::Blob.IntValue; };
	template <typename T>
	struct GetDataType < List<T> > { const static byte Type = (byte)SirenTypeId::List.IntValue; };
	template <typename TKey, typename TValue>
	struct GetDataType < Dictionary<TKey, TValue> > { const static byte Type = (byte)SirenTypeId::Dictionary.IntValue; };


}

template<typename T>
class SirenTraits
{
public:
	const static bool IsEnum = Compile::IsCustomEnum<T>::Value || std::is_enum<T>::value;
	const static bool HasDefaultValue = std::is_fundamental<T>::value || IsEnum;
	const static bool IsBasic = std::is_fundamental<T>::value;
	const static bool IsStruct = !IsBasic&&!std::is_same<T, HeapString>::value;


	typedef typename std::conditional<HasDefaultValue&&!std::is_pointer<T>::value, SirenBasicFieldMetadata<T>, SirenStructFieldMetadata<T>>::type MetadataType;


};


MEDUSA_END;
