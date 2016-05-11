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
//	template<typename TReader,typename TObject>
//	static bool DeserializeTo(TReader& hander, TObject& obj)
//	{
//		return false;
//	}
//}


struct SirenSchemaDeserializer
{

	template<typename TReader,typename TObject>
	static typename std::enable_if<Siren::HasCustomSerialization<TObject>::value, bool>::type Visit(TReader& hander, TObject& obj)
	{
		Siren::DeserializeTo(hander, obj);
		return true;
	}

	template<typename TReader,typename TObject>
	static typename std::enable_if<Siren::HasSchema<TObject>::value, bool>::type Visit(TReader& hander, TObject& obj)
	{
		//has schema
		hander.OnStructBegin();
		if (!VisitBaseFields<TReader,TObject, typename Siren::GetSchema<TObject>::Type>(hander, obj))
		{
			return false;
		}
		hander.OnStructEnd();
		return true;
	}

	template<typename TReader,typename TObject>
	static typename std::enable_if<std::is_pointer<TObject>::value, bool>::type Visit(TReader& hander, TObject& obj)
	{
		//is a struct and has schema
		typedef typename std::remove_pointer<TObject>::type RealObjectType;
		if (obj == nullptr)
		{
			obj = new RealObjectType();
		}
		return Visit(hander, *obj);
	}

	template<typename TReader, typename TObject>	//is enum
	static typename std::enable_if<SirenTraits<TObject>::IsEnum, bool>::type Visit(TReader& hander, TObject& obj)
	{
		int32 val;
		if (hander.OnValue(val))
		{
			obj = (TObject&)val;
			return true;
		}

		return false;
	}

	template<typename TReader,typename TObject>	//is basic
	static typename std::enable_if<SirenTraits<TObject>::IsBasic, bool>::type Visit(TReader& hander, TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}

	template<typename TReader, typename TObject >	//is string
	static typename std::enable_if<std::is_same<TObject, HeapString>::value, bool>::type Visit(TReader& hander, TObject& obj)
	{
		hander.OnValue(obj);
		return true;

	}

	template<typename TReader,typename TObject>	//is blob
	static typename std::enable_if<std::is_same<TObject, MemoryData>::value, bool>::type Visit(TReader& hander, TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}


	template<typename TReader,typename TObject>	//is list
	static bool Visit(TReader& hander, List<TObject>& obj)
	{
		uint outCount;
		byte outType;
		hander.OnListBegin(outType, outCount);
		obj.Clear();
		obj.ForceReserveCount(outCount);

		for(uint i=0;i<outCount;++i)
		{
			hander.OnListItemBegin(i);
			RETURN_FALSE_IF_FALSE(Visit(hander, obj[i]));
			hander.OnListItemEnd(i);
		}
		hander.OnListEnd();
		return true;
	}

	template<typename TReader, typename TKey, typename TValue>	//is dictionary
	static bool Visit(TReader& hander, Dictionary<TKey, TValue>& obj)
	{
		uint outCount;
		byte outKeyType;
		byte outValueType;

		hander.OnDictionaryBegin(outKeyType, outValueType, outCount);
		obj.Clear();
		obj.ForceReserve(outCount);

		typename Dictionary<TKey, TValue>::KeyType outKey;
        for(uint i=0;i<outCount;++i)
		{
			hander.OnDictionaryItemBegin(i);
			RETURN_FALSE_IF_FALSE(Visit(hander, outKey));
			hander.OnDictionaryKeyEnd(i);
			typename Dictionary<TKey, TValue>::TValueReferenceType outValue = obj.NewAdd(outKey);
			RETURN_FALSE_IF_FALSE(Visit(hander, outValue));
			hander.OnDictionaryItemEnd(i);

		}
		hander.OnDictionaryEnd();
		return true;
	}


	template<typename TReader, typename TObject, typename TSchemaType>
	static typename std::enable_if<Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseFields(TReader& hander, TObject& obj)
	{
		//find top base
		typedef typename TSchemaType::BaseType BaseObjectType;
		typedef typename Siren::GetSchema<BaseObjectType>::Type BaseSchemaType;

		if (!VisitBaseFields<TReader,BaseObjectType, BaseSchemaType>(hander, (BaseObjectType&)obj))
		{
			return false;
		}
		return VisitNextField<TReader,TObject, typename TSchemaType::Fields::Head, typename TSchemaType::Fields::Tail>(hander, obj);

	}

	template<typename TReader, typename TObject, typename TSchemaType>
	static typename std::enable_if<!Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseFields(TReader& hander, TObject& obj)
	{
		//has no base type
		return VisitNextField<TReader,TObject, typename TSchemaType::Fields::Head, typename TSchemaType::Fields::Tail>(hander, obj);
	}

	template<typename TReader, typename TObject, typename TFieldInfo, typename TNextFieldInfo>
	static typename std::enable_if<!std::is_same<TNextFieldInfo, void>::value, bool>::type VisitNextField(TReader& hander, TObject& obj)
	{
		if (!VisitNextFieldHelper<TReader,TObject, TFieldInfo>(hander, obj))
		{
			return false;
		}

		return VisitNextField<TReader,TObject, typename TNextFieldInfo::Head, typename TNextFieldInfo::Tail>(hander, obj);
	}

	template<typename TReader, typename TObject, typename TFieldInfo, typename TNextFieldInfo>
	static typename std::enable_if<std::is_same<TNextFieldInfo, void>::value, bool>::type VisitNextField(TReader& hander, TObject& obj)
	{
		return VisitNextFieldHelper<TReader,TObject, TFieldInfo>(hander, obj);
	}

	template<typename TReader, typename TObject, typename TFieldInfo>
	static typename std::enable_if<std::is_same<TFieldInfo, void>::value, bool>::type VisitNextFieldHelper(TReader& hander, TObject& obj)
	{
		return true;
	}

	template<typename TReader, typename TObject, typename TFieldInfo>
	static typename std::enable_if<!std::is_same<TFieldInfo, void>::value, bool>::type VisitNextFieldHelper(TReader& hander, TObject& obj)
	{
		while (true)
		{
			if (hander.IsEnd()&& TFieldInfo::IsRequired)
			{
				Log::FormatError("Reach end of file.Cannot find property:{}", TFieldInfo::Metadata.Name.c_str());
				hander.OnError();
				return false;
			}

			const typename TFieldInfo::MetadataType& metadata = TFieldInfo::Metadata;
			ushort id = TFieldInfo::Id;
			byte type = Siren::GetDataType<typename TFieldInfo::FieldType>::Type;
			ushort outId;
			byte outType;

			int result = hander.OnFieldBegin(metadata.Name, id, type, outId, outType);
			if (result == 0)
			{
				RETURN_FALSE_IF_FALSE(Visit(hander, TFieldInfo::Get(obj)));
				hander.OnFieldEnd();
				break;
			}
			else if (result < 0)
			{
				//miss field
				if (TFieldInfo::IsRequired)
				{
					//cannot find this property
					Log::FormatError("Cannot find property:{}", TFieldInfo::Metadata.Name);
					hander.OnError();
					return false;
				}
				else
				{
					TFieldInfo::SetToDefault(obj);
					break;
				}
			}
			else
			{
				//read unknown field
				//skip it
				hander.OnFieldSkip();
				//read next field
			}


		}

		return true;
	}
};

MEDUSA_END;
