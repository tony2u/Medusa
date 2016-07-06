// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenObjectSerializer.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"
#include "ISirenWriter.h"
#include "Core/Log/Log.h"
#include "Core/Siren/SirenObject.h"

MEDUSA_BEGIN;


bool SirenObjectSerializer::Serialize(const SirenObject& obj, const ISirenType& type, ISirenType* keyType/*=nullptr*/, ISirenType* valueType/*=nullptr*/)
{
	if (obj.Type() != type.Id())
	{
		Log::AssertFailedFormat("Cannot serialize type:{} to {}", obj.Type().ToString(), type.Id().ToString());
		return false;
	}

	switch (type.Id().ToInt())
	{
	case SirenTypeId::Bool.IntValue:
		return Visit(obj, (SirenBuildinBool&)type);
	case SirenTypeId::Int8.IntValue:
		return Visit(obj, (SirenBuildinInt8&)type);
	case SirenTypeId::UInt8.IntValue:
		return Visit(obj, (SirenBuildinUInt8&)type);
	case SirenTypeId::Int16.IntValue:
		return Visit(obj, (SirenBuildinInt16&)type);
	case SirenTypeId::UInt16.IntValue:
		return Visit(obj, (SirenBuildinUInt16&)type);
	case SirenTypeId::Int32.IntValue:
		return Visit(obj, (SirenBuildinInt32&)type);
	case SirenTypeId::UInt32.IntValue:
		return Visit(obj, (SirenBuildinUInt32&)type);
	case SirenTypeId::Int64.IntValue:
		return Visit(obj, (SirenBuildinInt64&)type);
	case SirenTypeId::UInt64.IntValue:
		return Visit(obj, (SirenBuildinUInt64&)type);
	case SirenTypeId::Float.IntValue:
		return Visit(obj, (SirenBuildinFloat&)type);
	case SirenTypeId::Double.IntValue:
		return Visit(obj, (SirenBuildinDouble&)type);
	case SirenTypeId::String.IntValue:
		return Visit(obj, (SirenBuildinString&)type);
	case SirenTypeId::Blob.IntValue:
		return Visit(obj, (SirenBuildinBlob&)type);
	case SirenTypeId::List.IntValue:
		if (valueType == nullptr)
		{
			Log::AssertFailedFormat("Cannot find list item type.");
			return false;
		}
		return Visit(obj, (SirenBuildinList&)type, *valueType);
	case SirenTypeId::Dictionary.IntValue:
		if (keyType == nullptr)
		{
			Log::AssertFailedFormat("Cannot find dictionary key type.");
			return false;
		}
		if (valueType == nullptr)
		{
			Log::AssertFailedFormat("Cannot find dictionary value type.");
			return false;
		}
		return Visit(obj, (SirenBuildinDictionary&)type, *keyType, *valueType);
	case SirenTypeId::Enum.IntValue:
		return Visit(obj, (SirenCustomEnum&)type);
	case SirenTypeId::Struct.IntValue:
		return Visit(obj, (SirenCustomClass&)type);
	default:
		break;
	}

	return false;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinBool& type)
{
	mWriter.OnValue(obj.GetBool());
	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinInt8& type)
{
	mWriter.OnValue(obj.GetInt8());
	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinUInt8& type)
{
	mWriter.OnValue(obj.GetUInt8());
	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinInt16& type)
{
	mWriter.OnValue(obj.GetInt16());
	return true;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinUInt16& type)
{
	mWriter.OnValue(obj.GetUInt16());
	return true;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinInt32& type)
{
	mWriter.OnValue(obj.GetInt32());
	return true;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinUInt32& type)
{
	mWriter.OnValue(obj.GetUInt32());
	return true;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinInt64& type)
{
	mWriter.OnValue(obj.GetInt64());
	return true;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinUInt64& type)
{
	mWriter.OnValue(obj.GetUInt64());
	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinFloat& type)
{
	mWriter.OnValue(obj.GetFloat());
	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinDouble& type)
{
	mWriter.OnValue(obj.GetDouble());
	return true;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinString& type)
{
	mWriter.OnValue(obj.GetString());
	return true;
}
bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinBlob& type)
{
	mWriter.OnValue(obj.GetBlob());
	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinList& type, const ISirenType& valueType)
{
	const auto& items = obj.GetList();
	uint count = (uint)items.Count();
	mWriter.OnListBegin((byte)valueType.Id().ToInt(), count);

	FOR_EACH_UINT32(i, count)
	{
		mWriter.OnListItemBegin(i);
		Serialize(items[i], valueType);
		mWriter.OnListItemEnd(i);
	}

	mWriter.OnListEnd(count);

	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenBuildinDictionary& type, const ISirenType& keyType, const ISirenType& valueType)
{
	mWriter.OnDictionaryBegin((byte)keyType.Id().ToInt(), (byte)valueType.Id().ToInt(), (uint)obj.Count());
	uint index = 0;
	for (const auto& item : obj.GetDictionary())
	{
		mWriter.OnDictionaryItemBegin(index);
		Serialize(item.Key, valueType);
		mWriter.OnDictionaryKeyEnd(index);
		Serialize(item.Value, valueType);
		mWriter.OnDictionaryItemEnd(index++);
	}

	mWriter.OnDictionaryEnd((uint)obj.Count());

	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenCustomEnum& type)
{
	//check enum valid
	if (!type.HasValue(obj.GetEnum()))
	{
		Log::AssertFailedFormat("Invalid enum value:{}", obj.GetEnum());
		return false;
	}

	mWriter.OnValue(obj.GetEnum());
	return true;
}

bool SirenObjectSerializer::Visit(const SirenObject& obj, const SirenCustomClass& type)
{
	mWriter.OnStructBegin();
	RETURN_FALSE_IF_FALSE(VisitFields(obj, type));
	mWriter.OnStructEnd();
	return true;
}

bool SirenObjectSerializer::VisitFields(const SirenObject& obj, const SirenCustomClass& type)
{
	SirenCustomClass* baseType = type.BaseType();
	if (baseType != nullptr)
	{
		RETURN_FALSE_IF_FALSE(VisitFields(obj, *baseType));
	}

	const auto& fields = type.Fields();
	for (auto& fieldPair : fields)
	{
		StringRef filedName = fieldPair.Key;
		SirenField* field = fieldPair.Value;
		SirenObject* fieldValue = obj.TryGetField(filedName);
		auto& defaultValue = field->DefaultValue();

		if (field->IsRequired())
		{
			if (!fieldValue->HasValue(defaultValue))
			{
				Log::FormatError("Forget to set {}::{}", type.Name(), filedName);
				mWriter.OnError();
				return false;
			}
		}
		else
		{
			if (!fieldValue->HasValue(defaultValue))
			{
				//ignore
				continue;
			}
		}

		auto fieldType = field->Type()->Id();
		mWriter.OnFieldBegin(filedName, field->Id(), (byte)fieldType.ToInt());
		Serialize(*fieldValue, *field->Type(), field->KeyType(), field->ValueType());
		mWriter.OnFieldEnd();
	}

	return true;
}

MEDUSA_END;