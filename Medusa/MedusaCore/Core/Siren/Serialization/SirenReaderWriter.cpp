// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenReaderWriter.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"
#include "ISirenReader.h"
#include "ISirenWriter.h"
#include "Core/Log/Log.h"
MEDUSA_BEGIN;

bool SirenReaderWriter::Run(const ISirenType& type, ISirenType* keyType /*= nullptr*/, ISirenType* valueType /*= nullptr*/)
{
	switch (type.Id().ToInt())
	{
	case SirenTypeId::Bool.IntValue:
		return Visit((SirenBuildinBool&)type);
	case SirenTypeId::Int8.IntValue:
		return Visit((SirenBuildinInt8&)type);
	case SirenTypeId::UInt8.IntValue:
		return Visit((SirenBuildinUInt8&)type);
	case SirenTypeId::Int16.IntValue:
		return Visit((SirenBuildinInt16&)type);
	case SirenTypeId::UInt16.IntValue:
		return Visit((SirenBuildinUInt16&)type);
	case SirenTypeId::Int32.IntValue:
		return Visit((SirenBuildinInt32&)type);
	case SirenTypeId::UInt32.IntValue:
		return Visit((SirenBuildinUInt32&)type);
	case SirenTypeId::Int64.IntValue:
		return Visit((SirenBuildinInt64&)type);
	case SirenTypeId::UInt64.IntValue:
		return Visit((SirenBuildinUInt64&)type);
	case SirenTypeId::Float.IntValue:
		return Visit((SirenBuildinFloat&)type);
	case SirenTypeId::Double.IntValue:
		return Visit((SirenBuildinDouble&)type);
	case SirenTypeId::String.IntValue:
		return Visit((SirenBuildinString&)type);
	case SirenTypeId::Blob.IntValue:
		return Visit((SirenBuildinBlob&)type);
	case SirenTypeId::List.IntValue:
		if (valueType == nullptr)
		{
			Log::AssertFailedFormat("Cannot find list item type.");
			return false;
		}
		return Visit((SirenBuildinList&)type, *valueType);
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
		return Visit((SirenBuildinDictionary&)type, *keyType, *valueType);
	case SirenTypeId::Enum.IntValue:
		return Visit((SirenCustomEnum&)type);
	case SirenTypeId::Struct.IntValue:
		return Visit((SirenCustomClass&)type);
	default:
		break;
	}

	return false;
}


bool SirenReaderWriter::Visit(const SirenBuildinBool& type)
{
	bool outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}

bool SirenReaderWriter::Visit(const SirenBuildinInt8& type)
{
	int8 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}

bool SirenReaderWriter::Visit(const SirenBuildinUInt8& type)
{
	uint8 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}

bool SirenReaderWriter::Visit(const SirenBuildinInt16& type)
{
	int16 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}
bool SirenReaderWriter::Visit(const SirenBuildinUInt16& type)
{
	uint16 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}
bool SirenReaderWriter::Visit(const SirenBuildinInt32& type)
{
	int32 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}
bool SirenReaderWriter::Visit(const SirenBuildinUInt32& type)
{
	uint32 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}
bool SirenReaderWriter::Visit(const SirenBuildinInt64& type)
{
	int64 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}
bool SirenReaderWriter::Visit(const SirenBuildinUInt64& type)
{
	uint64 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}

bool SirenReaderWriter::Visit(const SirenBuildinFloat& type)
{
	float outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}

bool SirenReaderWriter::Visit(const SirenBuildinDouble& type)
{
	double outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}
bool SirenReaderWriter::Visit(const SirenBuildinString& type)
{
	HeapString outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}
bool SirenReaderWriter::Visit(const SirenBuildinBlob& type)
{
	MemoryData outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));
	return mWriter.OnValue(outVal);
}

bool SirenReaderWriter::Visit(const SirenBuildinList& type, const ISirenType& valueType)
{
	uint outCount;
	byte outType;
	mReader.OnListBegin(outType, outCount);
	mWriter.OnListBegin(outType, outCount);
	for (uint i = 0; i < outCount; ++i)
	{
		mReader.OnListItemBegin(i);
		mWriter.OnListItemBegin(i);
		RETURN_FALSE_IF_FALSE(Run(valueType));

		mReader.OnListItemEnd(i);
		mWriter.OnListItemEnd(i);
	}
	mReader.OnListEnd();
	mWriter.OnListEnd(outCount);
	return true;
}

bool SirenReaderWriter::Visit(const SirenBuildinDictionary& type, const ISirenType& keyType, const ISirenType& valueType)
{
	uint outCount;
	byte outKeyType;
	byte outValueType;

	mReader.OnDictionaryBegin(outKeyType, outValueType, outCount);
	mWriter.OnDictionaryBegin(outKeyType, outValueType, outCount);

	SirenObject outKey;
	for (uint i = 0; i < outCount; ++i)
	{
		mReader.OnDictionaryItemBegin(i);
		mWriter.OnDictionaryItemBegin(i);

		RETURN_FALSE_IF_FALSE(Run(keyType));
		mReader.OnDictionaryKeyEnd(i);
		mWriter.OnDictionaryKeyEnd(i);

		RETURN_FALSE_IF_FALSE(Run(valueType));
		mReader.OnDictionaryItemEnd(i);
		mWriter.OnDictionaryItemEnd(i);

	}
	mReader.OnDictionaryEnd();
	mWriter.OnDictionaryEnd(outCount);

	return true;
}

bool SirenReaderWriter::Visit(const SirenCustomEnum& type)
{
	//check enum valid
	int32 outVal;
	RETURN_FALSE_IF_FALSE(mReader.OnValue(outVal));

	if (!type.HasValue(outVal))
	{
		Log::AssertFailedFormat("Invalid enum value:{}", outVal);
		return false;
	}

	return mWriter.OnValue(outVal);
}

bool SirenReaderWriter::Visit(const SirenCustomClass& type)
{
	mReader.OnStructBegin();
	mWriter.OnStructBegin();
	RETURN_FALSE_IF_FALSE(VisitFields(type));
	mReader.OnStructEnd();
	mWriter.OnStructEnd();
	return true;
}

bool SirenReaderWriter::VisitFields(const SirenCustomClass& type)
{
	SirenCustomClass* baseType = type.BaseType();
	if (baseType != nullptr)
	{
		RETURN_FALSE_IF_FALSE(VisitFields(*baseType));
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
				mWriter.OnError();
				return false;
			}

			int result = mReader.OnFieldBegin(filedName, field->Id(), (byte)fieldType.ToInt(), outId, outType);
			if (result == 0)
			{
				mWriter.OnFieldBegin(filedName, field->Id(), (byte)fieldType.ToInt());
				RETURN_FALSE_IF_FALSE(Run(*field->Type(), field->KeyType(), field->ValueType()));
				mReader.OnFieldEnd();
				mWriter.OnFieldEnd();
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
						mWriter.OnFieldBegin(filedName, field->Id(), (byte)fieldType.ToInt());
						mWriter.OnValue(defaultValue);
						mWriter.OnFieldEnd();
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