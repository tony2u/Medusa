// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenTraits.h"
#include "Core/Memory/MemoryData.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;


struct SirenSchemaChecker
{

	template<typename TWriter, typename TObject>
	static typename std::enable_if<Siren::HasSchema<TObject>::value, bool>::type Visit(TWriter& hander)
	{
		//has schema
		hander.OnStructBegin<TObject>();
		if (!VisitBaseFields<TWriter,TObject, typename Siren::GetSchema<TObject>::Type>(hander))
		{
			return false;
		}
		hander.OnStructEnd<TObject>();
		return true;
	}

	template<typename TWriter, typename TObject>	//is enum
	static typename std::enable_if<SirenTraits<TObject>::IsEnum, bool>::type Visit(TWriter& hander)
	{
		hander.OnValue<int>();
		return true;
	}

	template<typename TWriter, typename TObject>	//is basic
	static typename std::enable_if<SirenTraits<TObject>::IsBasic, bool>::type Visit(TWriter& hander)
	{
		hander.OnValue<TObject>();
		return true;
	}

	template<typename TWriter, typename TObject >	//is string
	static typename std::enable_if<std::is_same<TObject, HeapString>::value, bool>::type Visit(TWriter& hander)
	{
		hander.OnValue<HeapString>();
		return true;
	}

	template<typename TWriter, typename TObject>	//is blob
	static typename std::enable_if<std::is_same<TObject, MemoryData>::value,bool>::type Visit(TWriter& hander)
	{
		hander.OnValue<MemoryData>();
		return true;
	}


	template<typename TWriter, typename TObject>	//is list
	static typename std::enable_if<Siren::GetDataType<TObject>::Type==SirenTypeId::List.IntValue, bool>::type Visit(TWriter& hander)
	{
		hander.OnListBegin<TObject>();
		Visit<TWriter,Siren::GetDataType<TObject>::ItemType>(hander);
		hander.OnListEnd<TObject>();
		return true;
	}

	template<typename TWriter, typename TObject>	//is dictionary
	static typename std::enable_if<Siren::GetDataType<TObject>::Type == SirenTypeId::Dictionary.IntValue, bool>::type Visit(TWriter& hander)
	{
		hander.OnDictionaryBegin<TObject>();
		Visit<TWriter, Siren::GetDataType<TObject>::KeyType>(hander);
		Visit<TWriter, Siren::GetDataType<TObject>::ValueType>(hander);
		hander.OnDictionaryEnd<TObject>();
		return true;
	}


	template<typename TWriter, typename TObject, typename TSchemaType>
	static typename std::enable_if<Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseFields(TWriter& hander)
	{
		//find top base
		typedef typename TSchemaType::BaseType BaseObjectType;
		typedef typename Siren::GetSchema<BaseObjectType>::Type BaseSchemaType;

		if (!VisitBaseFields<TWriter,BaseObjectType, BaseSchemaType>(hander))
		{
			return false;
		}
		return VisitNextField<TWriter,TObject, typename TSchemaType::Fields::Head, typename TSchemaType::Fields::Tail>(hander);

	}

	template<typename TWriter, typename TObject, typename TSchemaType>
	static typename std::enable_if<!Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseFields(TWriter& hander)
	{
		//has no base type
		return VisitNextField<TWriter,TObject, typename TSchemaType::Fields::Head, typename TSchemaType::Fields::Tail>(hander);
	}

	template<typename TWriter, typename TObject, typename TFieldInfo, typename TNextFieldInfo>
	static typename std::enable_if<!std::is_same<TNextFieldInfo, void>::value,bool>::type VisitNextField(TWriter& hander)
	{
		if (!VisitNextFieldHelper<TWriter,TObject, TFieldInfo>(hander))
		{
			return false;
		}
		return VisitNextField<TWriter,TObject, typename TNextFieldInfo::Head, typename TNextFieldInfo::Tail>(hander);
	}

	template<typename TWriter, typename TObject, typename TFieldInfo, typename TNextFieldInfo>
	static typename std::enable_if<std::is_same<TNextFieldInfo, void>::value,bool>::type VisitNextField(TWriter& hander)
	{
		return VisitNextFieldHelper<TWriter,TObject, TFieldInfo>(hander);
	}

	template<typename TWriter, typename TObject, typename TFieldInfo>
	static typename std::enable_if<std::is_same<TFieldInfo,void>::value, bool>::type VisitNextFieldHelper(TWriter& hander)
	{

	}

	template<typename TWriter, typename TObject, typename TFieldInfo>
	static typename std::enable_if<!std::is_pointer<TObject>::value, bool>::type VisitNextFieldHelper(TWriter& hander)
	{
		const typename TFieldInfo::MetadataType& metadata = TFieldInfo::Metadata;

		ushort id = TFieldInfo::Id;
		byte type = Siren::GetDataType<typename TFieldInfo::FieldType>::Type;
		hander.OnFieldBegin<TObject>(metadata.Name,id,type);
		Visit<TWriter, typename TFieldInfo::FieldType>(hander);
		hander.OnFieldEnd<TObject>();
		return true;
	}

	template<typename TWriter, typename TObject, typename TFieldInfo>
	static typename std::enable_if<std::is_pointer<TObject>::value, bool>::type VisitNextFieldHelper(TWriter& hander)
	{
		const typename TFieldInfo::MetadataType& metadata = TFieldInfo::Metadata;

		hander.OnFieldBegin<TObject>(metadata.Name, id, type);
		Visit<TWriter, typename TFieldInfo::FieldType>(hander);
		hander.OnFieldEnd<TObject>();
		return true;
	}
};

MEDUSA_END;
