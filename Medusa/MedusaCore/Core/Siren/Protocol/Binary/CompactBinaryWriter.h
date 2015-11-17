// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseBinaryWriter.h"
#include "Core/Siren/SirenProtocol.h"
#include "Core/Utility/Utility.h"
#include "CompactBinarySizeCounter.h"
#include "Core/Siren/Reflection/StaticSchemaVisitor.h"

MEDUSA_SIREN_BEGIN;

template <typename TStream>
class CompactBinaryWriter : public BaseBinaryWriter < TStream >
{
public:
	static const uint16_t Magic = (uint16_t)SirenProtocol::Compact;
	typedef CompactBinarySizeCounter SizeCounter;
	typedef CompactBinaryWriter<TStream> Self;


	CompactBinaryWriter(TStream& output)
		: BaseBinaryWriter<TStream>(output)
	{
	}

	template<typename TObject>
	bool Run(const TObject& obj)
	{
		SizeCounter sizeCounter;
		RETURN_FALSE_IF_FALSE(sizeCounter.Run(obj));
		this->mStream.ReserveSize(sizeCounter.Size());
		return StaticSchemaVisitor::Visit(*this, obj);
	}

	void WriteVersion()
	{
		this->mStream.Write(Magic);
	}

	void OnStructBegin()
	{

	}

	void OnStructEnd()
	{
		this->mStream.Write((byte)SirenDataType::StructEnd.ToUInt());
	}

	void OnListBegin(byte itemType, uint count)
	{
		this->mStream.Write(itemType);
		this->WriteVariableUnsigned(count);

	}


	void OnListEnd()
	{
	}

	void OnDictionaryBegin(byte keyType, byte valueType, uint count)
	{
		this->mStream.Write(keyType);
		this->mStream.Write(valueType);

		this->WriteVariableUnsigned(count);
	}

	void OnDictionaryEnd()
	{

	}

	void OnPropertyBegin(const char* name, ushort nameLength, ushort id, byte type)
	{
		if (id <= 5)
		{
			this->mStream.Write(static_cast<uint8_t>(type | ((id) << 5)));
		}
		else if (id <= 0xff)
		{
			this->mStream.Write(static_cast<uint8_t>(type | (0x06 << 5)));
			this->mStream.Write(static_cast<uint8_t>(id));
		}
		else
		{
			this->mStream.Write(static_cast<uint8_t>(type | (0x07 << 5)));
			this->mStream.Write(id);
		}
	}

	void OnPropertyEnd()
	{

	}

	template<typename TObject>
	typename std::enable_if<std::is_floating_point<TObject>::value >::type OnValue(const TObject& obj)
	{
		this->mStream.Write(obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, bool>::value >::type OnValue(const TObject& obj)
	{
		this->mStream.Write(obj);
	}


	template<typename TObject>
	typename std::enable_if<std::is_unsigned<TObject>::value &&!std::is_same<TObject, bool>::value>::type OnValue(const TObject& obj)
	{
		this->WriteVariableUnsigned(obj);
	}

	template<typename TObject>
	typename std::enable_if<Compile::TypeTraits<TObject>::IsSignedInt >::type OnValue(const TObject& obj)
	{
		this->WriteVariableUnsigned(Utility::EncodeZigZag(obj));
	}


	template<typename TObject>
	typename std::enable_if<SirenTraits<TObject>::IsEnum >::type OnValue(const TObject& obj)
	{
		this->WriteVariableUnsigned((uint)obj);
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, HeapString>::value >::type OnValue(const TObject& obj)
	{
		this->WriteVariableUnsigned((uint)obj.Length() + 1);
		this->mStream.WriteString(obj);	//include '\0'
	}

	template<typename TObject>
	typename std::enable_if<std::is_same<TObject, MemoryByteData>::value >::type OnValue(const TObject& obj)
	{
		this->WriteVariableUnsigned((uint)obj.Size());
		this->mStream.WriteData(obj);
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		OnPropertyBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type);
		StaticSchemaVisitor::Visit(*this, obj);
		OnPropertyEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnProperty(const char* name, ushort nameLength, ushort id, const TObject& obj)
	{
		StaticSchemaVisitor::Visit(*this, obj);
	}


	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		StaticSchemaVisitor::Visit(*this, obj);
	}
};


MEDUSA_SIREN_END;
