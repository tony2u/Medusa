// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "SirenMacro.h"
#include "Core/Siren/Reflection/BasicPropertyMetadata.h"
#include "Core/Siren/Reflection/StructPropertyMetadata.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Siren/SirenDataType.h"
#include "Core/Siren/SirenDefines.h"

MEDUSA_SIREN_BEGIN;

//template <typename TWriter, typename T>
//void Serialize(TWriter& writer, const T& obj)
//{
//
//}
//
//template <typename TReader, typename T>
//bool Deserialize(TReader& reader, const T& outObj)
//{
//	return true;
//}


template <typename T, typename Enable = void>
struct IsCustomEnum
{
	const static bool Value = false;
};

template <typename T>
struct IsCustomEnum < T, typename std::enable_if<T::IsEnum>::type >
{
	const static bool Value = true;
};





template <typename T, typename Enable = void>
struct GetSchema;

template <typename T>
struct GetSchema < T, typename std::enable_if<std::is_class<typename T::Schema::Properties>::value>::type >
{
	typedef typename T::Schema Type;
};


template <typename T, typename Enable = void>
struct HasSchema : std::false_type {};

template <typename T>
struct HasSchema<T, typename std::enable_if<std::is_class<typename GetSchema<T>::Type>::value>::type> : std::true_type{};


template <typename T, typename Enable = void>
struct HasBaseType :std::false_type {};

template <typename T>
struct HasBaseType<T, typename std::enable_if<!std::is_same<typename T::BaseType, void>::value>::type> : std::true_type{};





template <typename T>
struct GetDataType { const static byte Type = (byte)SirenDataType::Struct.IntValue; };
template <>
struct GetDataType < bool > { const static byte Type = (byte)SirenDataType::Bool.IntValue; };
template <>
struct GetDataType < char > { const static byte Type = (byte)SirenDataType::Int8.IntValue; };
template <>
struct GetDataType < byte > { const static byte Type = (byte)SirenDataType::UInt8.IntValue; };
template <>
struct GetDataType < short > { const static byte Type = (byte)SirenDataType::Int16.IntValue; };
template <>
struct GetDataType < ushort > { const static byte Type = (byte)SirenDataType::UInt16.IntValue; };
template <>
struct GetDataType < int > { const static byte Type = (byte)SirenDataType::Int32.IntValue; };
template <>
struct GetDataType < uint > { const static byte Type = (byte)SirenDataType::UInt32.IntValue; };
template <>
struct GetDataType < int64 > { const static byte Type = (byte)SirenDataType::Int64.IntValue; };
template <>
struct GetDataType < uint64 > { const static byte Type = (byte)SirenDataType::UInt64.IntValue; };
template <>
struct GetDataType < HeapString > { const static byte Type = (byte)SirenDataType::String.IntValue; };
template <>
struct GetDataType < Blob > { const static byte Type = (byte)SirenDataType::Blob.IntValue; };
template <typename T>
struct GetDataType < List<T> > { const static byte Type = (byte)SirenDataType::List.IntValue; };
template <typename TKey, typename TValue>
struct GetDataType < Dictionary<TKey, TValue> > { const static byte Type = (byte)SirenDataType::Dictionary.IntValue; };


template<typename T>
class SirenTraits
{
public:
	const static bool IsEnum = IsCustomEnum<T>::Value || std::is_enum<T>::value;
	const static bool HasDefaultValue = std::is_fundamental<T>::value || IsEnum;
	const static bool IsBasic = std::is_fundamental<T>::value || std::is_enum<T>::value || IsEnum;
	const static bool IsStruct = !IsBasic&&!std::is_same<T, HeapString>::value;


	typedef typename std::conditional<HasDefaultValue&&!std::is_pointer<T>::value, BasicPropertyMetadata<T>, StructPropertyMetadata<T>>::type MetadataType;


};

MEDUSA_SIREN_END;
