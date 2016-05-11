// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseSirenBinaryWriter.h"
#include "Core/Siren/Code/SirenCoderType.h"
#include "Core/Utility/Utility.h"
#include "SirenCompactBinarySizeCounter.h"

MEDUSA_BEGIN;

class SirenCompactBinaryWriter : public BaseSirenBinaryWriter
{
public:
	using BaseSirenBinaryWriter::BaseSirenBinaryWriter;

	
	virtual bool OnValue(bool val) override { this->mStream.Write(val);  return true; }
	virtual bool OnValue(char val)override { return this->WriteVariableUnsigned(Utility::EncodeZigZag(val)); }
	virtual bool OnValue(byte val) override { return WriteVariableUnsigned(val); }
	virtual bool OnValue(short val) override { return this->WriteVariableUnsigned(Utility::EncodeZigZag(val)); }
	virtual bool OnValue(ushort val) override { return WriteVariableUnsigned(val); }
	virtual bool OnValue(int32 val)override { return this->WriteVariableUnsigned(Utility::EncodeZigZag(val)); }
	virtual bool OnValue(uint32 val)override { return WriteVariableUnsigned(val); }
	virtual bool OnValue(int64 val) override { return this->WriteVariableUnsigned(Utility::EncodeZigZag(val)); }
	virtual bool OnValue(uint64 val)override { return WriteVariableUnsigned(val); }
	virtual bool OnValue(float val) override { this->mStream.Write(val); return true; }
	virtual bool OnValue(double val) override { this->mStream.Write(val); return true; }
	virtual bool OnValue(const StringRef& val)override 
	{
		this->WriteVariableUnsigned((uint)val.Length());
		this->mStream.WriteString(val, false);

		return true; 
	}
	virtual bool OnValue(const MemoryData& val) override 
	{
		this->WriteVariableUnsigned((uint)val.Size());
		this->mStream.WriteData(val);
		return true;
	}


	virtual bool OnStructEnd()override
	{
		this->mStream.Write((byte)SirenTypeId::Null.ToUInt());
		return true;
	}

	virtual bool OnListBegin(byte itemType, uint count)override
	{
		this->mStream.Write(itemType);
		this->WriteVariableUnsigned(count);
		return true;
	}

	virtual bool OnDictionaryBegin(byte keyType, byte valueType, uint count)override
	{
		this->mStream.Write(keyType);
		this->mStream.Write(valueType);

		this->WriteVariableUnsigned(count);
		return true;
	}


	virtual bool OnFieldBegin(const StringRef& name, ushort id, byte type)override
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
		return true;
	}

	
	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type);
		SirenSchemaSerializer::Visit(*this, obj);
		OnFieldEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		SirenSchemaSerializer::Visit(*this, obj);
	}


	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		SirenSchemaSerializer::Visit(*this, obj);
	}
};


MEDUSA_END;
