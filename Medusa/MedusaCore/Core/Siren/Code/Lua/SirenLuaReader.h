// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "Core/Siren/Serialization/ISirenReader.h"
#include "Core/Lua/LuaRef.h"
#include "Core/Lua/LuaState.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"
MEDUSA_BEGIN;

class SirenLuaReader :public ISirenReader
{
public:
	SirenLuaReader(lua_State* state)
		:mState(state,false)
	{

	}

	virtual bool OnValue(bool& obj) override{return OnValueHelper(obj);}
	virtual bool OnValue(char& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(int8& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(uint8& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(int16& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(uint16& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(int32& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(uint32& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(int64& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(uint64& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(float& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(double& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(HeapString& obj) override { return OnValueHelper(obj); }
	virtual bool OnValue(MemoryData& obj) override { return OnValueHelper(obj); }

	virtual bool OnStructBegin()override
	{
		return true;
	}

	virtual bool OnStructEnd()override
	{
		return true;
	}

	virtual bool OnListBegin(byte& outValueType, uint& outCount)override
	{
		LuaStack s(mState.GetState());
		outCount=(uint)s.RawLength();
		return true;
	}

	virtual bool OnListItemBegin(uint index)override
	{
		LuaStack s(mState.GetState());
		return s.RawPushFieldAt((int)index);
		return true;
	}

	virtual bool OnDictionaryBegin(byte& outKeyType, byte& outValueType, uint& outCount)override
	{
		LuaStack s(mState.GetState());
		outCount = (uint)s.FieldCount();

		//begin iteration
		lua_pushnil(mState.GetState());//first key
		return true;
	}


	virtual bool OnDictionaryItemBegin(uint index)override 
	{ 
		if (lua_next(mState.GetState(), -2) != 0)
		{
			//duplicate key to pop out
			LuaStack s(mState.GetState());
			//key,value
			s.Duplicate(-2);	//key,value,key
			return true;
		}
		return false;
	}

	virtual bool OnDictionaryItemEnd(uint index)override
	{
		return true; 
	}

	virtual int OnFieldBegin(const StringRef& name, ushort id, byte type, ushort& outId, byte& outType)override
	{
		LuaStack s(mState.GetState());
		bool isSuccess = s.RawPushField(name);
		if (isSuccess)
		{
			SirenTypeId typeId = (SirenTypeId)type;
			//check type
			switch (s.GetType())
			{
			case LUA_TBOOLEAN:
				RETURN_ZERO_IF_EQUAL(typeId, SirenTypeId::Bool);
				break;
			case LUA_TNUMBER:
				switch (typeId.ToInt())
				{
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
				case SirenTypeId::Enum.IntValue:
					return 0;
					break;
				default:
					break;
				}
				break;
			case LUA_TSTRING:
				RETURN_ZERO_IF_EQUAL(typeId, SirenTypeId::String);
				RETURN_ZERO_IF_EQUAL(typeId, SirenTypeId::Blob);
				break;
			case LUA_TTABLE:
				RETURN_ZERO_IF_EQUAL(typeId, SirenTypeId::List);
				RETURN_ZERO_IF_EQUAL(typeId, SirenTypeId::Dictionary);
				RETURN_ZERO_IF_EQUAL(typeId, SirenTypeId::Struct);

				break;
			case LUA_TFUNCTION:
			case LUA_TUSERDATA:
			case LUA_TTHREAD:
			case LUA_TLIGHTUSERDATA:
			default:
				break;
			}

			Log::FormatError("Inconsistent field type:{} to {}", s.GetTypeName(), typeId.ToString());
		}

		s.PopNoReturn();
		return -1;
	}

	virtual bool OnFieldEnd()override
	{
		return true;
	}

	virtual bool OnFieldSkip()override
	{
		return true;
	}

	template<typename TObject, bool TWithHeader = true>
	void OnField(const char* name, ushort nameLength, ushort id, TObject& outObj)
	{
		ushort outId;
		byte outType;
		OnFieldBegin(name, nameLength, id, Siren::GetDataType<TObject>::Type, outId, outType);
		SirenSchemaDeserializer::Visit(*this, outObj);
		OnFieldEnd();
	}

	template<typename TObject>
	void OnStruct(TObject& outObj)
	{
		SirenSchemaDeserializer::Visit(*this, outObj);
	}

	template<typename T>
	bool OnValueHelper(T& obj)
	{
		LuaStack s(mState.GetState());
		obj = s.Pop<T>();
		return true;
	}
private:
	LuaState mState;
};


MEDUSA_END;
#endif