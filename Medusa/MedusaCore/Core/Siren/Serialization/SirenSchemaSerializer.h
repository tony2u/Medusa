// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenTraits.h"
#include "Core/Memory/MemoryData.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

//namespace Siren
//{
//	template<typename TWriter, typename TObject>
//	static void Serialize(TWriter& hander, const TObject& obj)
//	{
//
//	}
//}

template<bool TIsForceWriteDefault=false>
struct SirenSchemaSerializer
{

	template<typename TWriter, typename TObject>
	static typename std::enable_if<Siren::HasCustomSerialization<TObject>::value, bool>::type Visit(TWriter& hander, const TObject& obj)
	{
		Siren::Serialize(hander, obj);
		return true;
	}

	template<typename TWriter, typename TObject>
	static typename std::enable_if<Siren::HasSchema<TObject>::value, bool>::type Visit(TWriter& hander, const TObject& obj)
	{
		//has schema
		hander.OnStructBegin();
		if (!VisitBaseFields<TWriter,TObject, typename Siren::GetSchema<TObject>::Type>(hander, obj))
		{
			return false;
		}
		hander.OnStructEnd();
		return true;
	}

	template<typename TWriter, typename TObject>
	static typename std::enable_if<std::is_pointer<TObject>::value, bool>::type Visit(TWriter& hander, const TObject& obj)
	{
		//is a struct and has schema
		typedef typename std::remove_pointer<TObject>::type RealObjectType;
		hander.OnStructBegin();
		if (!VisitBaseFields<TWriter,RealObjectType, typename Siren::GetSchema<RealObjectType>::Type>(hander, *obj))
		{
			return false;
		}
		hander.OnStructEnd();
		return true;
	}

	template<typename TWriter, typename TObject>	//is enum
	static typename std::enable_if<SirenTraits<TObject>::IsEnum, bool>::type Visit(TWriter& hander, const TObject& obj)
	{
		hander.OnValue((int)obj);
		return true;
	}

	template<typename TWriter, typename TObject>	//is basic
	static typename std::enable_if<SirenTraits<TObject>::IsBasic, bool>::type Visit(TWriter& hander, const TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}

	template<typename TWriter, typename TObject >	//is string
	static typename std::enable_if<std::is_same<TObject, HeapString>::value, bool>::type Visit(TWriter& hander, const TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}

	template<typename TWriter, typename TObject>	//is blob
	static typename std::enable_if<std::is_same<TObject, MemoryData>::value,bool>::type Visit(TWriter& hander, const TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}


	template<typename TWriter, typename TObject>	//is list
	static bool Visit(TWriter& hander, const List<TObject>& obj)
	{
		uint count = (uint)obj.Count();
		hander.OnListBegin(Siren::GetDataType<TObject>::Type,(uint)count);
		FOR_EACH_UINT32(i, count)
		{
			hander.OnListItemBegin(i);
			RETURN_FALSE_IF_FALSE(Visit(hander, obj[i]));
			hander.OnListItemEnd(i);
		}

		hander.OnListEnd(count);
		return true;
	}

	template<typename TWriter, typename TKey, typename TValue>	//is dictionary
	static bool Visit(TWriter& hander, const Dictionary<TKey, TValue>& obj)
	{
		uint count = (uint)obj.Count();
		hander.OnDictionaryBegin(Siren::GetDataType<TKey>::Type, Siren::GetDataType<TValue>::Type,count);
		uint index = 0;
		for (auto i : obj)
		{
			hander.OnDictionaryItemBegin(index);
			RETURN_FALSE_IF_FALSE(Visit(hander, i.Key));
			hander.OnDictionaryKeyEnd(index);
			RETURN_FALSE_IF_FALSE(Visit(hander, i.Value));
			hander.OnDictionaryItemEnd(index++);
		}
		hander.OnDictionaryEnd(count);
		return true;
	}


	template<typename TWriter, typename TObject, typename TSchemaType>
	static typename std::enable_if<Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseFields(TWriter& hander, const TObject& obj)
	{
		//find top base
		typedef typename TSchemaType::BaseType BaseObjectType;
		typedef typename Siren::GetSchema<BaseObjectType>::Type BaseSchemaType;

		if (!VisitBaseFields<TWriter,BaseObjectType, BaseSchemaType>(hander, (const BaseObjectType&)obj))
		{
			return false;
		}
		return VisitNextField<TWriter,TObject, typename TSchemaType::Fields::Head, typename TSchemaType::Fields::Tail>(hander, obj);

	}

	template<typename TWriter, typename TObject, typename TSchemaType>
	static typename std::enable_if<!Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseFields(TWriter& hander, const TObject& obj)
	{
		//has no base type
		return VisitNextField<TWriter,TObject, typename TSchemaType::Fields::Head, typename TSchemaType::Fields::Tail>(hander, obj);
	}

	template<typename TWriter, typename TObject, typename TFieldInfo, typename TNextFieldInfo>
	static typename std::enable_if<!std::is_same<TNextFieldInfo, void>::value,bool>::type VisitNextField(TWriter& hander, const TObject& obj)
	{
		if (!VisitNextFieldHelper<TWriter,TObject, TFieldInfo>(hander, obj))
		{
			return false;
		}
		return VisitNextField<TWriter,TObject, typename TNextFieldInfo::Head, typename TNextFieldInfo::Tail>(hander, obj);
	}

	template<typename TWriter, typename TObject, typename TFieldInfo, typename TNextFieldInfo>
	static typename std::enable_if<std::is_same<TNextFieldInfo, void>::value,bool>::type VisitNextField(TWriter& hander, const TObject& obj)
	{
		return VisitNextFieldHelper<TWriter,TObject, TFieldInfo>(hander, obj);
	}

	template<typename TWriter, typename TObject, typename TFieldInfo>
	static typename std::enable_if<std::is_same<TFieldInfo,void>::value, bool>::type VisitNextFieldHelper(TWriter& hander, const TObject& obj)
	{
		return true;
	}

	template<typename TWriter, typename TObject, typename TFieldInfo>
	static typename std::enable_if<!std::is_same<TFieldInfo, void>::value&&!std::is_pointer<TObject>::value, bool>::type VisitNextFieldHelper(TWriter& hander, const TObject& obj)
	{
		const typename TFieldInfo::MetadataType& metadata = TFieldInfo::Metadata;

		if (TFieldInfo::IsRequired)
		{
			if (!TFieldInfo::HasValue(obj))
			{
				//error need to set value
				Log::FormatError("Forget to set {}::{}", Siren::GetSchema<typename TFieldInfo::ClassType>::Type::Metadata.Name.c_str(), TFieldInfo::Metadata.Name.c_str());
				hander.OnError();
				return false;
			}
		}
		else
		{
			if (!TFieldInfo::HasValue(obj))
			{
				//no set value
				if (!TIsForceWriteDefault)
				{
					return true;
				}
			}

		}

		ushort id = TFieldInfo::Id;
		byte type = Siren::GetDataType<typename TFieldInfo::FieldType>::Type;
		hander.OnFieldBegin(metadata.Name,id,type);

		RETURN_FALSE_IF_FALSE(Visit(hander, TFieldInfo::Get(obj)));
		hander.OnFieldEnd();
		return true;
	}

	template<typename TWriter, typename TObject, typename TFieldInfo>
	static typename std::enable_if<std::is_pointer<TObject>::value, bool>::type VisitNextFieldHelper(TWriter& hander, const TObject& obj)
	{
		const typename TFieldInfo::MetadataType& metadata = TFieldInfo::Metadata;

		if (TFieldInfo::IsRequired)
		{
			if (obj==nullptr)
			{
				//error need to set value
				Log::FormatError("Forget to set {}::{}", GetSchema<typename TFieldInfo::ClassType>::Type::Metadata.Name.c_str(), TFieldInfo::Metadata.Name.c_str());
				hander.OnError();
				return false;
			}
		}
		else
		{
			if (obj==nullptr)
			{
				//no set value
				if (!TIsForceWriteDefault)
				{
					return true;
				}
			}

		}

		ushort id = TFieldInfo::Id;
		byte type = Siren::GetDataType<typename TFieldInfo::FieldType>::Type;
		hander.OnFieldBegin(metadata.Name, id, type);

		RETURN_FALSE_IF_FALSE(Visit(hander, TFieldInfo::Get(obj)));
		hander.OnFieldEnd();
		return true;
	}
};

MEDUSA_END;
