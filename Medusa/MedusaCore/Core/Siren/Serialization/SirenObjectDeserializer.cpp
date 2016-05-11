// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenObjectDeserializer.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"
#include "ISirenReader.h"
#include "Core/Siren/SirenObject.h"
#include "Core/Log/Log.h"
MEDUSA_BEGIN;

bool SirenObjectDeserializer::Deserialize(SirenObject& obj, const ISirenType& type, ISirenType* keyType /*= nullptr*/, ISirenType* valueType /*= nullptr*/)
{
	obj.SetType(type.Id());

	/*if (obj.Type() != )
	{
		Log::AssertFailedFormat("Cannot deserialize type:{} to {}", obj.Type().ToString(), type.Id().ToString());
		return false;
	}*/

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


bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinBool& type)
{
	return mReader.OnValue(obj.MutableBool());
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinInt8& type)
{
	return mReader.OnValue(obj.MutableInt8());
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinUInt8& type)
{
	return mReader.OnValue(obj.MutableUInt8());
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinInt16& type)
{
	return mReader.OnValue(obj.MutableInt16());
}
bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinUInt16& type)
{
	return mReader.OnValue(obj.MutableUInt16());
}
bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinInt32& type)
{
	return mReader.OnValue(obj.MutableInt32());
}
bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinUInt32& type)
{
	return mReader.OnValue(obj.MutableUInt32());
}
bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinInt64& type)
{
	return mReader.OnValue(obj.MutableInt64());
}
bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinUInt64& type)
{
	return mReader.OnValue(obj.MutableUInt64());
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinFloat& type)
{
	return mReader.OnValue(obj.MutableFloat());
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinDouble& type)
{
	return mReader.OnValue(obj.MutableDouble());
}
bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinString& type)
{
	return mReader.OnValue(obj.MutableString());
}
bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinBlob& type)
{
	return mReader.OnValue(obj.MutableBlob());
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinList& type, const ISirenType& valueType)
{
	uint outCount;
	byte outType;
	mReader.OnListBegin(outType, outCount);
	auto& mutableItems= obj.MutableList();
	mutableItems.Clear();
	mutableItems.ForceReserveCount(outCount);

	for (uint i = 0; i < outCount; ++i)
	{
		mReader.OnListItemBegin(i);
		RETURN_FALSE_IF_FALSE(Deserialize(mutableItems[i], valueType));
		mReader.OnListItemEnd(i);
	}
	mReader.OnListEnd();
	return true;
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenBuildinDictionary& type, const ISirenType& keyType, const ISirenType& valueType)
{
	uint outCount;
	byte outKeyType;
	byte outValueType;

	mReader.OnDictionaryBegin(outKeyType, outValueType, outCount);
	auto& mutableItems = obj.MutableDictionary();

	mutableItems.Clear();
	mutableItems.ForceReserve(outCount);

	SirenObject outKey;
	for (uint i = 0; i < outCount; ++i)
	{
		mReader.OnDictionaryItemBegin(i);
		RETURN_FALSE_IF_FALSE(Deserialize(outKey, keyType));
		mReader.OnDictionaryKeyEnd(i);
		SirenObject& outValue = mutableItems.NewAdd(outKey);
		RETURN_FALSE_IF_FALSE(Deserialize(outValue, valueType));
		mReader.OnDictionaryItemEnd(i);
	}
	mReader.OnDictionaryEnd();
	return true;
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenCustomEnum& type)
{
	//check enum valid
	RETURN_FALSE_IF_FALSE(mReader.OnValue(obj.MutableEnum()));

	if (!type.HasValue(obj.GetEnum()))
	{
		Log::AssertFailedFormat("Invalid enum value:{}", obj.GetEnum());
		return false;
	}
	return true;
}

bool SirenObjectDeserializer::Visit(SirenObject& obj, const SirenCustomClass& type)
{
	mReader.OnStructBegin();
	RETURN_FALSE_IF_FALSE(VisitFields(obj, type));
	mReader.OnStructEnd();
	return true;
}

bool SirenObjectDeserializer::VisitFields(SirenObject& obj, const SirenCustomClass& type)
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
		auto fieldType = field->Type()->Id();

		ushort outId;
		byte outType;
		while (true)
		{
			if (mReader.IsEnd() && field->IsRequired())
			{
				Log::FormatError("Reach end of file.Cannot find property:{}", filedName);
				mReader.OnError();
				return false;
			}

			int result = mReader.OnFieldBegin(filedName, field->Id(), (byte)fieldType.ToInt(), outId, outType);
			if (result == 0)
			{
				SirenObject& fieldObj = obj.NewField(filedName);
				RETURN_FALSE_IF_FALSE(Deserialize(fieldObj, *field->Type(), field->KeyType(), field->ValueType()));
				mReader.OnFieldEnd();
				break;
			}
			else if (result < 0)
			{
				//miss field
				if (field->IsRequired())
				{
					//cannot find this property
					Log::FormatError("Cannot find property:{}", filedName);
					mReader.OnError();
					return false;
				}
				else
				{
					auto& defaultValue = field->DefaultValue();
					if (!defaultValue.IsNull())
					{
						SirenObject& fieldObj = obj.NewField(filedName);
						fieldObj = defaultValue;
						break;

					}
				}
			}
			else
			{
				//read unknown field
				//skip it
				mReader.OnFieldSkip();
				//read next field
			}
		}

	}

	return true;
}

MEDUSA_END;