// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Protocol/Json/JsonInputStream.h"
#include "Core/Coder/Crypt/Base91Decoder.h"
#include "Core/Collection/Stack.h"
#include "Core/Siren/SirenProtocol.h"
#include "Core/Siren/Reflection/DynamicSchemaVisitor.h"
#include "CoreLib/Common/rapidjson.h"

MEDUSA_SIREN_BEGIN;

template <typename TStream>
class JsonReader
{
public:
	static const uint16_t Magic = (uint16_t)SirenProtocol::Json;

	JsonReader(TStream& output)
		: mStream(output)
	{
	}

	template<typename TObject>
	bool Run(TObject& obj)
	{
		mDoc.ParseStream<rapidjson::kParseStopWhenDoneFlag>(mStream);
		if (mDoc.HasParseError())
		{
			Log::FormatError("Json Parse error! offset %u - {}", (unsigned)mDoc.GetErrorOffset(), GetParseError_En(mDoc.GetParseError()));
			return false;
		}
		mJsonValues.Push(&mDoc);
		mArrayIndices.Push(-1);
		return DynamicSchemaVisitor::Visit(*this, obj);
	}

	void ReadVersion()
	{

	}

	void OnStructBegin()
	{
		const rapidjson::Value* currentJsonValue = mJsonValues.Top();
		int refIndex = mArrayIndices.Top();
		if (refIndex >= 0)
		{
			currentJsonValue = &(currentJsonValue->operator []((uint)refIndex));
			mJsonValues.Push(currentJsonValue);
			mArrayIndices.Push(-2);
		}
	}

	void OnStructEnd()
	{
		int refIndex = mArrayIndices.Top();
		if (refIndex == -2)
		{
			mJsonValues.Pop();
			mArrayIndices.Pop();
		}
	}

	void OnArrayStep(uint index)
	{
		mArrayIndices.MutableTop() = (int)index;
	}

	void OnListBegin(byte& outValueType, uint& outCount)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		outCount = currentJsonValue->Capacity();
	}

	void OnListEnd()
	{
	}

	void OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		outCount = currentJsonValue->Capacity() / 2;	//key and value
	}

	void OnDictionaryEnd()
	{

	}

	int OnPropertyBegin(const char* name, ushort nameLength, ushort id, byte type, ushort& outId, byte& outType)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();

		rapidjson::Value::ConstMemberIterator itr = currentJsonValue->FindMember(name);
		if (itr == currentJsonValue->MemberEnd())
		{
			return -1;
		}
		mJsonValues.Push(&itr->value);
		mArrayIndices.Push(-1);
		return 0;
	}

	void OnPropertyEnd()
	{
		mJsonValues.Pop();
		mArrayIndices.Pop();
	}

	void OnPropertySkip()
	{
		mJsonValues.Pop();
		mArrayIndices.Pop();
	}

	template<typename TObject>
	typename std::enable_if<std::is_floating_point<TObject>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetDouble();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, bool>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetBool();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, char>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetInt();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, short>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetInt();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, int>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetInt();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, int64>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetInt64();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, byte>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetUint();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, ushort>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetUint();
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, uint>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetUint();
	}
	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, uint64>::value >::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetUint64();
	}

	template<typename TObject>
	typename std::enable_if<SirenTraits<TObject>::IsEnum>::type OnValue(TObject& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		obj = (TObject)currentJsonValue->GetUint();
	}

	void OnString(HeapString& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		uint length = currentJsonValue->GetStringLength();
		obj.ReserveLength(length);
		obj.Append(currentJsonValue->GetString());
	}

	void OnMemoryData(MemoryByteData& obj)
	{
		const rapidjson::Value* currentJsonValue = CurrentValue();
		uint length = currentJsonValue->GetStringLength();
		Base91Decoder decoder;
		obj = decoder.Code(StringRef(currentJsonValue->GetString(), length));
	}


	const rapidjson::Value* CurrentValue()
	{
		const rapidjson::Value* currentJsonValue = mJsonValues.Top();
		int refIndex = mArrayIndices.Top();
		if (refIndex >= 0)
		{
			return &(currentJsonValue->operator []((uint)refIndex));
		}
		return currentJsonValue;
	}
	void OnError()
	{

	}

	bool IsEnd()const
	{
		return false;
	}

	template<typename TObject, bool TWithHeader = true>
	void OnProperty(const char* name, ushort nameLength, ushort id, TObject& outObj)
	{
		ushort outId;
		byte outType;
		OnPropertyBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type, outId, outType);
		DynamicSchemaVisitor::Visit(*this, outObj);
		OnPropertyEnd();
	}

	template<typename TObject>
	void OnStruct(TObject& outObj)
	{
		DynamicSchemaVisitor::Visit(*this, outObj);
	}
private:
	JsonInputStream<TStream> mStream;
	rapidjson::Document mDoc;
	rapidjson::Value* mJsonValue;
	Stack<const rapidjson::Value*> mJsonValues;
	Stack<int> mArrayIndices;
};


MEDUSA_SIREN_END;