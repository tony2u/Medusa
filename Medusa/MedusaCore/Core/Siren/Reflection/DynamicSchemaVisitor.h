// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenTraits.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_SIREN_BEGIN;

template<typename THandler, typename TObject>
static bool DeserializeTo(THandler& hander, TObject& obj)
{
	return false;
}

struct DynamicSchemaVisitor
{

	template<typename THandler, typename TObject>
	static typename std::enable_if<Siren::HasCustomSerialization<TObject>::value, bool>::type Visit(THandler& hander, TObject& obj)
	{
		Siren::DeserializeTo(hander, obj);
		return true;
	}

	template<typename THandler, typename TObject>
	static typename std::enable_if<Siren::HasSchema<TObject>::value, bool>::type Visit(THandler& hander, TObject& obj)
	{
		//has schema
		hander.OnStructBegin();
		if (!VisitBaseProperties<THandler, TObject, typename GetSchema<TObject>::Type>(hander, obj))
		{
			return false;
		}
		hander.OnStructEnd();
		return true;
	}

	template<typename THandler, typename TObject>
	static typename std::enable_if<std::is_pointer<TObject>::value, bool>::type Visit(THandler& hander, TObject& obj)
	{
		//is a struct and has schema
		typedef typename std::remove_pointer<TObject>::type RealObjectType;
		if (obj == nullptr)
		{
			obj = new RealObjectType();
		}
		return Visit(hander, *obj);
	}

	template<typename THandler, typename TObject>	//is basic
	static typename std::enable_if<SirenTraits<TObject>::IsBasic, bool>::type Visit(THandler& hander, TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}

	template<typename THandler, typename TObject >	//is string
	static typename std::enable_if<std::is_same<TObject, HeapString>::value, bool>::type Visit(THandler& hander, TObject& obj)
	{
		hander.OnString(obj);
		return true;

	}

	template<typename THandler, typename TObject>	//is blob
	static typename std::enable_if<std::is_same<TObject, MemoryByteData>::value, bool>::type Visit(THandler& hander, TObject& obj)
	{
		hander.OnMemoryData(obj);
		return true;
	}


	template<typename THandler, typename TObject>	//is list
	static bool Visit(THandler& hander, List<TObject>& obj)
	{
		uint outCount;
		byte outType;
		hander.OnListBegin(outType, outCount);
		obj.Clear();
		obj.ForceReserveCount(outCount);

		for(uint i=0;i<outCount;++i)
		{
			hander.OnArrayStep(i);
			RETURN_FALSE_IF_FALSE(Visit(hander, obj[i]));
		}
		hander.OnListEnd();
		return true;
	}

	template<typename THandler, typename TKey, typename TValue>	//is dictionary
	static bool Visit(THandler& hander, Dictionary<TKey, TValue>& obj)
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
			hander.OnArrayStep(i * 2);
			RETURN_FALSE_IF_FALSE(Visit(hander, outKey));
			hander.OnArrayStep(i * 2 + 1);
			typename Dictionary<TKey, TValue>::TValueReferenceType outValue = obj.NewAdd(outKey);
			RETURN_FALSE_IF_FALSE(Visit(hander, outValue));
		}
		hander.OnDictionaryEnd();
		return true;
	}


	template<typename THandler, typename TObject, typename TSchemaType>
	static typename std::enable_if<Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseProperties(THandler& hander, TObject& obj)
	{
		//find top base
		typedef typename TSchemaType::BaseType BaseObjectType;
		typedef typename GetSchema<BaseObjectType>::Type BaseSchemaType;

		if (!VisitBaseProperties<THandler, BaseObjectType, BaseSchemaType>(hander, (BaseObjectType&)obj))
		{
			return false;
		}
		return VisitNextProperty<THandler, TObject, typename TSchemaType::Properties::Head, typename TSchemaType::Properties::Tail>(hander, obj);

	}

	template<typename THandler, typename TObject, typename TSchemaType>
	static typename std::enable_if<!Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseProperties(THandler& hander, TObject& obj)
	{
		//has no base type
		return VisitNextProperty<THandler, TObject, typename TSchemaType::Properties::Head, typename TSchemaType::Properties::Tail>(hander, obj);
	}

	template<typename THandler, typename TObject, typename TPropertyInfo, typename TNextPropertyInfo>
	static typename std::enable_if<!std::is_same<TNextPropertyInfo, void>::value, bool>::type VisitNextProperty(THandler& hander, TObject& obj)
	{
		if (!VisitNextPropertyHelper<THandler, TObject, TPropertyInfo>(hander, obj))
		{
			return false;
		}

		return VisitNextProperty<THandler, TObject, typename TNextPropertyInfo::Head, typename TNextPropertyInfo::Tail>(hander, obj);
	}

	template<typename THandler, typename TObject, typename TPropertyInfo, typename TNextPropertyInfo>
	static typename std::enable_if<std::is_same<TNextPropertyInfo, void>::value, bool>::type VisitNextProperty(THandler& hander, TObject& obj)
	{
		return VisitNextPropertyHelper<THandler, TObject, TPropertyInfo>(hander, obj);
	}

	template<typename THandler, typename TObject, typename TPropertyInfo>
	static typename std::enable_if<std::is_same<TPropertyInfo, void>::value, bool>::type VisitNextPropertyHelper(THandler& hander, TObject& obj)
	{
		return true;
	}

	template<typename THandler, typename TObject, typename TPropertyInfo>
	static typename std::enable_if<!std::is_same<TPropertyInfo, void>::value, bool>::type VisitNextPropertyHelper(THandler& hander, TObject& obj)
	{
		while (true)
		{
			if (hander.IsEnd()&& TPropertyInfo::IsRequired)
			{
				Log::FormatError("Reach end of file.Cannot find property:{}", TPropertyInfo::Metadata.Name.c_str());
				hander.OnError();
				return false;
			}

			const typename TPropertyInfo::MetadataType& metadata = TPropertyInfo::Metadata;
			ushort id = TPropertyInfo::Id;
			byte type = Siren::GetDataType<typename TPropertyInfo::PropertyType>::Type;
			ushort outId;
			byte outType;

			int result = hander.OnPropertyBegin(metadata.Name.c_str(), (ushort)metadata.Name.Length(), id, type, outId, outType);
			if (result == 0)
			{
				RETURN_FALSE_IF_FALSE(Visit(hander, TPropertyInfo::Get(obj)));
				hander.OnPropertyEnd();
				break;
			}
			else if (result < 0)
			{
				//miss field
				if (TPropertyInfo::IsRequired)
				{
					//cannot find this property
					Log::FormatError("Cannot find property:{}", TPropertyInfo::Metadata.Name.c_str());
					hander.OnError();
					return false;
				}
				else
				{
					TPropertyInfo::SetToDefault(obj);
					break;
				}
			}
			else
			{
				//read unknown field
				//skip it
				hander.OnPropertySkip();
				//read next field
			}


		}

		return true;
	}
};

MEDUSA_SIREN_END;
