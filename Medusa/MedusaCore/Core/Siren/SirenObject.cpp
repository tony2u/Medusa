// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenObject.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


SirenObject::SirenObject(const MemoryData& val)
	:mType(SirenTypeId::Blob)
{
	mData.Blob = new MemoryData();
	*mData.Blob = val.Clone();
}

SirenObject::SirenObject(const StringRef& val)
	: mType(SirenTypeId::String)
{
	mData.String = new HeapString(val);
}

SirenObject::SirenObject(const char* val)
	: mType(SirenTypeId::String)
{
	mData.String = new HeapString(val);
}

SirenObject::SirenObject(const ListData& val)
	: mType(SirenTypeId::List)
{
	mData.List = new ListData(val);
}

SirenObject::SirenObject(const DictionaryData& val)
	: mType(SirenTypeId::List)
{
	mData.Dictionary = new DictionaryData(val);
}


SirenObject::SirenObject(const SirenObject& other)
	:mType(other.mType)
{
	switch (mType.ToInt())
	{
	case SirenTypeId::Blob.IntValue:
		mData.Blob = new MemoryData();
		*mData.Blob = other.mData.Blob->Clone();
		break;
	case SirenTypeId::String.IntValue:
		mData.String = new HeapString(*other.mData.String);
		break;
	case SirenTypeId::List.IntValue:
		mData.List = new ListData(*other.mData.List);
		break;
	case SirenTypeId::Dictionary.IntValue:
		mData.Dictionary = new DictionaryData(*other.mData.Dictionary);
		break;
	case SirenTypeId::Struct.IntValue:
		mData.Fields = new FieldDictionary(*other.mData.Fields);
		break;
	default:
		//copy data
		mData = other.mData;
		break;
	}
}

bool SirenObject::operator==(const SirenObject& other) const
{
	if (this == &other)
	{
		return true;
	}

	if (mType != other.mType)
	{
		return false;
	}

	switch (mType.ToInt())
	{
	case SirenTypeId::Blob.IntValue:
	case SirenTypeId::List.IntValue:
	case SirenTypeId::Dictionary.IntValue:
	case SirenTypeId::Struct.IntValue:
		return false;
	case SirenTypeId::String.IntValue:
		return *mData.String == *other.mData.String;
	case SirenTypeId::Bool.IntValue:return Math::IsEqual(mData.Bool, other.mData.Bool);
	case SirenTypeId::Int8.IntValue:return Math::IsEqual(mData.Int8, other.mData.Int8);
	case SirenTypeId::UInt8.IntValue:return Math::IsEqual(mData.UInt8, other.mData.UInt8);
	case SirenTypeId::Int16.IntValue:return Math::IsEqual(mData.Int16, other.mData.Int16);
	case SirenTypeId::UInt16.IntValue:return Math::IsEqual(mData.UInt16, other.mData.UInt16);
	case SirenTypeId::Int32.IntValue:return Math::IsEqual(mData.Int32, other.mData.Int32);
	case SirenTypeId::UInt32.IntValue:return Math::IsEqual(mData.UInt32, other.mData.UInt32);
	case SirenTypeId::Int64.IntValue:return Math::IsEqual(mData.Int64, other.mData.Int64);
	case SirenTypeId::UInt64.IntValue:return Math::IsEqual(mData.UInt64, other.mData.UInt64);
	case SirenTypeId::Float.IntValue:return Math::IsEqual(mData.Float, other.mData.Float);
	case SirenTypeId::Double.IntValue:return Math::IsEqual(mData.Double, other.mData.Double);
	case SirenTypeId::Enum.IntValue:return Math::IsEqual(mData.Enum, other.mData.Enum);

	default:
		return Memory::Compare(&mData, &other.mData, sizeof(Data)) == 0;
		break;
	}

}


bool SirenObject::operator!=(const SirenObject& other) const
{
	return !this->operator==(other);
}


SirenObject& SirenObject::operator=(const SirenObject& other)
{
	if (this != &other)
	{
		this->~SirenObject();
		mType = other.mType;

		switch (mType.ToInt())
		{
		case SirenTypeId::Blob.IntValue:
			mData.Blob = new MemoryData();
			*mData.Blob = other.mData.Blob->Clone();
			break;
		case SirenTypeId::String.IntValue:
			mData.String = new HeapString(*other.mData.String);
			break;
		case SirenTypeId::List.IntValue:
			mData.List = new ListData(*other.mData.List);
			break;
		case SirenTypeId::Dictionary.IntValue:
			mData.Dictionary = new DictionaryData(*other.mData.Dictionary);
			break;
		case SirenTypeId::Struct.IntValue:
			mData.Fields = new FieldDictionary(*other.mData.Fields);
			break;
		default:
			//copy data
			mData = other.mData;
			break;
		}
	}
	return *this;
}

SirenObject::SirenObject(SirenObject&& other)
	:mType(other.mType)
{
	mData = other.mData;

	other.mType = SirenTypeId::Null;
	other.ClearData();
}



SirenObject& SirenObject::operator=(SirenObject&& other)
{
	if (this != &other)
	{
		mType = other.mType;
		mData = other.mData;

		other.mType = SirenTypeId::Null;
		other.ClearData();
	}
	return *this;
}

SirenObject::~SirenObject(void)
{
	Destroy();
}

void SirenObject::ClearData()
{
	Memory::ClearZero(&mData);
}

void SirenObject::AssertType(SirenTypeId type) const
{
	Log::AssertFormat(mType == type, "Cannot get data from {} to {}", mType.ToString(), type.ToString());
}

void SirenObject::PrintHelper(HeapString& str, uintp depth /*= 0*/, bool withPrefix /*= true*/) const
{
	if (withPrefix)
	{
		str.Append('\t', depth);
	}
	//print self
	switch (mType.ToInt())
	{
	case SirenTypeId::Bool.IntValue:
		str.AppendFormat("{}\n",  mData.Bool);
		break;
	case SirenTypeId::Int8.IntValue:
		str.AppendFormat("{}\n",  mData.Int8);
		break;
	case SirenTypeId::UInt8.IntValue:
		str.AppendFormat("{}\n",  mData.UInt8);
		break;
	case SirenTypeId::Int16.IntValue:
		str.AppendFormat("{}\n",  mData.Int16);
		break;
	case SirenTypeId::UInt16.IntValue:
		str.AppendFormat("{}\n",  mData.UInt16);
		break;
	case SirenTypeId::Int32.IntValue:
		str.AppendFormat("{}\n",  mData.Int32);
		break;
	case SirenTypeId::UInt32.IntValue:
		str.AppendFormat("{}\n",  mData.UInt32);
		break;
	case SirenTypeId::Int64.IntValue:
		str.AppendFormat("{}\n",  mData.Int64);
		break;
	case SirenTypeId::UInt64.IntValue:
		str.AppendFormat("{}\n",  mData.UInt64);
		break;
	case SirenTypeId::Float.IntValue:
		str.AppendFormat("{}\n",  mData.Float);
		break;
	case SirenTypeId::Double.IntValue:
		str.AppendFormat("{}\n",  mData.Double);
		break;
	case SirenTypeId::String.IntValue:
		str.AppendFormat("\"{}\"\n",  *mData.String);
		break;
	case SirenTypeId::Blob.IntValue:
		str.AppendFormat("[{}]\n",  mData.Blob->Size());
		break;
	case SirenTypeId::List.IntValue:
		str.AppendFormat("[{}]\n",  mData.List->Count());
		for (auto& item : *mData.List)
		{
			item.PrintHelper(str, depth + 1);
		}
		break;
	case SirenTypeId::Dictionary.IntValue:
		str.AppendFormat("[{}]\n",  mData.Dictionary->Count());
		for (auto& itemPair : *mData.Dictionary)
		{
			str.Append('\t', depth);
			itemPair.Key.PrintHelper(str, depth + 1, false);
			str.Append(" = ");
			itemPair.Value.PrintHelper(str, depth + 1, false);
		}
		break;
	case SirenTypeId::Enum.IntValue:
		str.AppendFormat("({})\n",  mData.Enum);
		break;
	case SirenTypeId::Struct.IntValue:
		str.AppendLine();
		for (auto& itemPair : *mData.Fields)
		{
			str.Append('\t', depth);
			str.AppendFormat("{}:", itemPair.Key);
			itemPair.Value.PrintHelper(str, depth + 1, false);
		}
		break;

	default:
		break;
	}
}

intp SirenObject::HashCode() const
{
	intp type = mType.ToInt();
	return type;
}

bool SirenObject::HasValue(const SirenObject& defaultValue) const
{
	if (defaultValue.IsNull())
	{
		switch (mType.ToInt())
		{
		case SirenTypeId::Bool.IntValue:
		case SirenTypeId::Int8.IntValue:
		case SirenTypeId::UInt8.IntValue:
		case SirenTypeId::Int16.IntValue:
		case SirenTypeId::UInt16.IntValue:
		case SirenTypeId::Int32.IntValue:
		case SirenTypeId::UInt32.IntValue:
		case SirenTypeId::Int64.IntValue:
		case SirenTypeId::UInt64.IntValue:
		case SirenTypeId::Float.IntValue:
		case SirenTypeId::Double.IntValue:
			return true;
		case SirenTypeId::String.IntValue:
			return !mData.String->IsEmpty();
		case SirenTypeId::Blob.IntValue:
			return !mData.Blob->IsEmpty();
		case SirenTypeId::List.IntValue:
			return mData.List->IsEmpty();
		case SirenTypeId::Dictionary.IntValue:
			return mData.Dictionary->IsEmpty();
		case SirenTypeId::Enum.IntValue:
			return true;
		case SirenTypeId::Struct.IntValue:
			return true;
		default:
			return true;
		}
	}
	else
	{
		switch (mType.ToInt())
		{
		case SirenTypeId::Blob.IntValue:
		case SirenTypeId::List.IntValue:
		case SirenTypeId::Dictionary.IntValue:
		case SirenTypeId::Struct.IntValue:
			return true;
		default:
			return *this == defaultValue;
		}
	}

}

void SirenObject::SetValue(const StringRef& val)
{
	switch (mType.ToInt())
	{
	case SirenTypeId::Bool.IntValue:
		mData.Bool = StringParser::StringTo<decltype(mData.Bool)>(val);
		break;
	case SirenTypeId::Int8.IntValue:
		mData.Int8 = (int8)StringParser::ToInt(val);
		break;
	case SirenTypeId::UInt8.IntValue:
		mData.UInt8 = (uint8)StringParser::ToUInt(val);
		break;
	case SirenTypeId::Int16.IntValue:
		mData.Int16 = (int16)StringParser::ToInt(val);
		break;
	case SirenTypeId::UInt16.IntValue:
		mData.UInt16 = (uint16)StringParser::ToUInt(val);
		break;
	case SirenTypeId::Int32.IntValue:
		mData.Int32 = (int32)StringParser::ToInt(val);
		break;
	case SirenTypeId::UInt32.IntValue:
		mData.UInt32 = (uint32)StringParser::ToUInt(val);
		break;
	case SirenTypeId::Int64.IntValue:
		mData.Int64 = (int64)StringParser::ToInt(val);
		break;
	case SirenTypeId::UInt64.IntValue:
		mData.UInt64 = (uint64)StringParser::ToUInt(val);
		break;
	case SirenTypeId::Float.IntValue:
		mData.Float = StringParser::StringTo<decltype(mData.Float)>(val);
		break;
	case SirenTypeId::Double.IntValue:
		mData.Double = StringParser::StringTo<decltype(mData.Double)>(val);
		break;
	case SirenTypeId::String.IntValue:
		*mData.String = val;
		break;
	case SirenTypeId::Enum.IntValue:
		mData.Enum = (int32)StringParser::ToInt(val);
		break;
	case SirenTypeId::Blob.IntValue:
	case SirenTypeId::List.IntValue:
	case SirenTypeId::Dictionary.IntValue:
	case SirenTypeId::Struct.IntValue:
	default:
		break;
	}
}

void SirenObject::SetTypeAndValue(SirenTypeId type, const StringRef& val)
{
	SetType(type);
	SetValue(val);
}

size_t SirenObject::Count() const
{
	if (mType == SirenTypeId::List)
	{
		return mData.List->Count();
	}
	if (mType == SirenTypeId::Dictionary)
	{
		return mData.Dictionary->Count();
	}

	Log::AssertFailedFormat("Cannot get count on type:{}", mType.ToString());
	return 0;

}

HeapString SirenObject::Print() const
{
	HeapString str;
	PrintHelper(str);
	return str;
}

void SirenObject::SetType(SirenTypeId val)
{
	RETURN_IF_EQUAL(mType, val);
	Destroy();
	mType = val;

	switch (mType.ToInt())
	{
	case SirenTypeId::Blob.IntValue:
		mData.Blob = new MemoryData();
		break;
	case SirenTypeId::String.IntValue:
		mData.String = new HeapString();
		break;
	case SirenTypeId::List.IntValue:
		mData.List = new ListData();
		break;
	case SirenTypeId::Dictionary.IntValue:
		mData.Dictionary = new DictionaryData();
		break;
	case SirenTypeId::Struct.IntValue:
		mData.Fields = new FieldDictionary();
		break;
	default:
		break;
	}
}

void SirenObject::Destroy()
{
	switch (mType.ToInt())
	{
	case SirenTypeId::Blob.IntValue:
		SAFE_DELETE(mData.Blob);
		break;
	case SirenTypeId::String.IntValue:
		SAFE_DELETE(mData.String);
		break;
	case SirenTypeId::List.IntValue:
		SAFE_DELETE(mData.List);
		break;
	case SirenTypeId::Dictionary.IntValue:
		SAFE_DELETE(mData.Dictionary);
		break;
	case SirenTypeId::Struct.IntValue:
		SAFE_DELETE(mData.Fields);
		break;
	default:
		break;
	}
	mType = SirenTypeId::Null;
}

const SirenObject SirenObject::Null;


MEDUSA_END;