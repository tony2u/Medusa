// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Code/Json/SirenJsonInputStream.h"
#include "Core/Coder/Crypt/Base91Decoder.h"
#include "Core/Collection/Stack.h"
#include "Core/Siren/Code/SirenCoderType.h"
#include "CoreLib/Common/rapidjson.h"
#include "Core/Siren/Serialization/ISirenReader.h"

MEDUSA_BEGIN;

class SirenJsonReader:public ISirenReader
{
public:
	SirenJsonReader(IStream& output)
		: mStream(output)
	{
		mDoc.ParseStream<rapidjson::kParseStopWhenDoneFlag>(mStream);
		if (mDoc.HasParseError())
		{
			Log::FormatError("Json Parse error! offset %u - {}", (unsigned)mDoc.GetErrorOffset(), GetParseError_En(mDoc.GetParseError()));
			//throw exception
		}
		mJsonValues.Push(&mDoc);
		mListIndices.Push(-1);
	}

	virtual bool OnValue(bool& obj) override 
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (bool)currentJsonValue->GetBool();
		return true;
	}
	virtual bool OnValue(char& obj) override 
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (char)currentJsonValue->GetInt();
		return true;
	}
	virtual bool OnValue(byte& obj) override 
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (byte)currentJsonValue->GetUint();
		return true;
	}
	virtual bool OnValue(short& obj) override 
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (short)currentJsonValue->GetInt();
		return true;
	}
	virtual bool OnValue(ushort& obj)override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (ushort)currentJsonValue->GetUint();
		return true;
	}
	virtual bool OnValue(int32& obj) override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (int32)currentJsonValue->GetInt();
		return true;
	}
	virtual bool OnValue(uint32& obj) override 
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (uint32)currentJsonValue->GetUint();
		return true;
	}
	virtual bool OnValue(int64& obj)override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (int64)currentJsonValue->GetInt64();
		return true;
	}
	virtual bool OnValue(uint64& obj)override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (uint64)currentJsonValue->GetUint64();
		return true;
	}
	virtual bool OnValue(float& obj) override 
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (float)currentJsonValue->GetDouble(); 
		return true;
	}
	virtual bool OnValue(double& obj)override 
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (double)currentJsonValue->GetDouble();
		return true;
	}

	virtual bool OnValue(HeapString& obj) override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		uint length = currentJsonValue->GetStringLength();
		obj.ReserveLength(length);
		obj.Append(currentJsonValue->GetString());

		return true;
	}

	virtual bool OnValue(MemoryData& obj)override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		uint length = currentJsonValue->GetStringLength();
		Base91Decoder decoder;
		obj = decoder.Code(StringRef(currentJsonValue->GetString(), length));
		return true;
	}

	virtual bool OnStructBegin()override
	{
		const rapidjson::Value* currentJsonValue = mJsonValues.Top();
		int refIndex = mListIndices.Top();
		if (refIndex >= 0)
		{
			currentJsonValue = &(currentJsonValue->operator []((uint)refIndex));
			mJsonValues.Push(currentJsonValue);
			mListIndices.Push(-2);
		}
		return true;
	}

	virtual bool OnStructEnd()override
	{
		int refIndex = mListIndices.Top();
		if (refIndex == -2)
		{
			mJsonValues.Pop();
			mListIndices.Pop();
		}
		return true;

	}

	virtual bool OnListBegin(byte& outValueType, uint& outCount)override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		outCount = currentJsonValue->Capacity();
		return true;

	}
	virtual bool OnListItemBegin(uint index)override
	{
		mListIndices.MutableTop() = (int)index;
		return true;
	}

	virtual bool OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		outCount = currentJsonValue->Capacity() / 2;	//key and value
		return true;

	}
	virtual bool OnDictionaryItemBegin(uint index)override
	{
		mListIndices.MutableTop() = (int)index;
		return true;
	}

	virtual bool OnDictionaryKeyEnd(uint index)override
	{
		mListIndices.MutableTop() = (int)index+1;
		return true;

	}
	
	virtual int OnFieldBegin(const StringRef& name, ushort id, byte type, ushort& outId, byte& outType)override
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();

		rapidjson::Value::ConstMemberIterator itr = currentJsonValue->FindMember(name.c_str());
		if (itr == currentJsonValue->MemberEnd())
		{
			return -1;
		}
		mJsonValues.Push(&itr->value);
		mListIndices.Push(-1);
		return 0;
	}

	virtual bool OnFieldEnd()override
	{
		mJsonValues.Pop();
		mListIndices.Pop();
		return true;

	}

	virtual bool OnFieldSkip()override
	{
		mJsonValues.Pop();
		mListIndices.Pop();
		return true;

	}



	const rapidjson::Value* CurrentValue()
	{
		const rapidjson::Value* currentJsonValue = mJsonValues.Top();
		int refIndex = mListIndices.Top();
		if (refIndex >= 0)
		{
			return &(currentJsonValue->operator []((uint)refIndex));
		}
		return currentJsonValue;
	}


	template<typename TObject, bool TWithHeader = true>
	void OnField(const StringRef& name, ushort id, TObject& outObj)
	{
		ushort outId;
		byte outType;
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type, outId, outType);
		SirenSchemaDeserializer::Visit(*this, outObj);
		OnFieldEnd();
	}

	template<typename TObject>
	void OnStruct(TObject& outObj)
	{
		SirenSchemaDeserializer::Visit(*this, outObj);
	}
private:
	SirenJsonInputStream mStream;
	rapidjson::Document mDoc;
	Stack<const rapidjson::Value*> mJsonValues;
	Stack<int> mListIndices;
};


MEDUSA_END;