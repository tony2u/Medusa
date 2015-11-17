// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenTraits.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_SIREN_BEGIN;

template<typename THandler, typename TObject>
static void Serialize(THandler& hander, const TObject& obj)
{

}

struct StaticSchemaVisitor
{

	template<typename THandler, typename TObject>
	static typename std::enable_if<Siren::HasCustomSerialization<TObject>::value, bool>::type Visit(THandler& hander, const TObject& obj)
	{
		Siren::Serialize<THandler,TObject>(hander, obj);
		return true;
	}



	template<typename THandler, typename TObject>
	static typename std::enable_if<Siren::HasSchema<TObject>::value, bool>::type Visit(THandler& hander, const TObject& obj)
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
	static typename std::enable_if<std::is_pointer<TObject>::value, bool>::type Visit(THandler& hander, const TObject& obj)
	{
		//is a struct and has schema
		typedef typename std::remove_pointer<TObject>::type RealObjectType;
		hander.OnStructBegin();
		if (!VisitBaseProperties<THandler, RealObjectType, typename GetSchema<RealObjectType>::Type>(hander, *obj))
		{
			return false;
		}
		hander.OnStructEnd();
		return true;
	}

	template<typename THandler, typename TObject>	//is basic
	static typename std::enable_if<SirenTraits<TObject>::IsBasic, bool>::type Visit(THandler& hander, const TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}

	template<typename THandler, typename TObject >	//is string
	static typename std::enable_if<std::is_same<TObject, HeapString>::value, bool>::type Visit(THandler& hander, const TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}

	template<typename THandler, typename TObject>	//is blob
	static typename std::enable_if<std::is_same<TObject, MemoryByteData>::value,bool>::type Visit(THandler& hander, const TObject& obj)
	{
		hander.OnValue(obj);
		return true;
	}


	template<typename THandler, typename TObject>	//is list
	static bool Visit(THandler& hander, const List<TObject>& obj)
	{
		uint count = (uint)obj.Count();
		hander.OnListBegin(Siren::GetDataType<TObject>::Type,(uint)count);
		FOR_EACH_SIZE(i, count)
		{
			RETURN_FALSE_IF_FALSE(Visit(hander, obj[i]));
		}

		hander.OnListEnd();
		return true;
	}

	template<typename THandler, typename TKey, typename TValue>	//is dictionary
	static bool Visit(THandler& hander, const Dictionary<TKey, TValue>& obj)
	{
		uint count = (uint)obj.Count();
		hander.OnDictionaryBegin(Siren::GetDataType<TKey>::Type, Siren::GetDataType<TValue>::Type,count);
		FOR_EACH_COLLECTION(i, obj)
		{
			RETURN_FALSE_IF_FALSE(Visit(hander, i->Key));
			RETURN_FALSE_IF_FALSE(Visit(hander, i->Value));
		}
		hander.OnDictionaryEnd();
		return true;
	}


	template<typename THandler, typename TObject, typename TSchemaType>
	static typename std::enable_if<Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseProperties(THandler& hander, const TObject& obj)
	{
		//find top base
		typedef typename TSchemaType::BaseType BaseObjectType;
		typedef typename GetSchema<BaseObjectType>::Type BaseSchemaType;

		if (!VisitBaseProperties<THandler, BaseObjectType, BaseSchemaType>(hander, (const BaseObjectType&)obj))
		{
			return false;
		}
		return VisitNextProperty<THandler, TObject, typename TSchemaType::Properties::Head, typename TSchemaType::Properties::Tail>(hander, obj);

	}

	template<typename THandler, typename TObject, typename TSchemaType>
	static typename std::enable_if<!Siren::HasBaseType<TSchemaType>::value, bool>::type VisitBaseProperties(THandler& hander, const TObject& obj)
	{
		//has no base type
		return VisitNextProperty<THandler, TObject, typename TSchemaType::Properties::Head, typename TSchemaType::Properties::Tail>(hander, obj);
	}

	template<typename THandler, typename TObject, typename TPropertyInfo, typename TNextPropertyInfo>
	static typename std::enable_if<!std::is_same<TNextPropertyInfo, void>::value,bool>::type VisitNextProperty(THandler& hander, const TObject& obj)
	{
		if (!VisitNextPropertyHelper<THandler, TObject, TPropertyInfo>(hander, obj))
		{
			return false;
		}
		return VisitNextProperty<THandler, TObject, typename TNextPropertyInfo::Head, typename TNextPropertyInfo::Tail>(hander, obj);
	}

	template<typename THandler, typename TObject, typename TPropertyInfo, typename TNextPropertyInfo>
	static typename std::enable_if<std::is_same<TNextPropertyInfo, void>::value,bool>::type VisitNextProperty(THandler& hander, const TObject& obj)
	{
		return VisitNextPropertyHelper<THandler, TObject, TPropertyInfo>(hander, obj);
	}

	template<typename THandler, typename TObject, typename TPropertyInfo>
	static typename std::enable_if<std::is_same<TPropertyInfo,void>::value, bool>::type VisitNextPropertyHelper(THandler& hander, const TObject& obj)
	{

	}

	template<typename THandler, typename TObject, typename TPropertyInfo>
	static typename std::enable_if<!std::is_pointer<TObject>::value, bool>::type VisitNextPropertyHelper(THandler& hander, const TObject& obj)
	{
		const typename TPropertyInfo::MetadataType& metadata = TPropertyInfo::Metadata;

		if (TPropertyInfo::IsRequired)
		{
			if (!TPropertyInfo::HasValue(obj))
			{
				//error need to set value
				Log::FormatError("Forget to set {}::{}", GetSchema<typename TPropertyInfo::ClassType>::Type::Metadata.Name.c_str(), TPropertyInfo::Metadata.Name.c_str());
				hander.OnError();
				return false;
			}
		}
		else
		{
			if (!TPropertyInfo::HasValue(obj))
			{
				//no set value
				return true;
			}

		}

		ushort id = TPropertyInfo::Id;
		byte type = Siren::GetDataType<typename TPropertyInfo::PropertyType>::Type;
		hander.OnPropertyBegin(metadata.Name.c_str(), (ushort)metadata.Name.Length(), id,type);

		RETURN_FALSE_IF_FALSE(Visit(hander, TPropertyInfo::Get(obj)));
		hander.OnPropertyEnd();
		return true;
	}

	template<typename THandler, typename TObject, typename TPropertyInfo>
	static typename std::enable_if<std::is_pointer<TObject>::value, bool>::type VisitNextPropertyHelper(THandler& hander, const TObject& obj)
	{
		const typename TPropertyInfo::MetadataType& metadata = TPropertyInfo::Metadata;

		if (TPropertyInfo::IsRequired)
		{
			if (obj==nullptr)
			{
				//error need to set value
				Log::FormatError("Forget to set {}::{}", GetSchema<typename TPropertyInfo::ClassType>::Type::Metadata.Name.c_str(), TPropertyInfo::Metadata.Name.c_str());
				hander.OnError();
				return false;
			}
		}
		else
		{
			if (obj==nullptr)
			{
				//no set value
				return true;
			}

		}

		ushort id = TPropertyInfo::Id;
		byte type = Siren::GetDataType<typename TPropertyInfo::PropertyType>::Type;
		hander.OnPropertyBegin(metadata.Name.c_str(), metadata.Name.Length(), id, type);

		RETURN_FALSE_IF_FALSE(Visit(hander, TPropertyInfo::Get(obj)));
		hander.OnPropertyEnd();
		return true;
	}
};

MEDUSA_SIREN_END;
