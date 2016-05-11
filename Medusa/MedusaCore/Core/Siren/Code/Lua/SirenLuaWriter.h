// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "Core/Siren/Serialization/ISirenWriter.h"
#include "Core/Lua/LuaRef.h"
#include "Core/Lua/LuaState.h"

MEDUSA_BEGIN;

class SirenLuaWriter : public ISirenWriter
{
public:
	SirenLuaWriter(lua_State* state)
		:mState(state, false), mTargetObject(nullptr)
	{

	}
	SirenLuaWriter(LuaRef obj)
		:mState(obj.State(), false), mTargetObject(obj)
	{

	}

	virtual bool OnValue(bool val) override { return OnValueHelper(val); }
	virtual bool OnValue(char val)override { return OnValueHelper(val); }
	virtual bool OnValue(byte val) override { return OnValueHelper(val); }
	virtual bool OnValue(short val) override { return OnValueHelper(val); }
	virtual bool OnValue(ushort val) override { return OnValueHelper(val); }
	virtual bool OnValue(int32 val)override { return OnValueHelper(val); }
	virtual bool OnValue(uint32 val)override { return OnValueHelper(val); }
	virtual bool OnValue(int64 val) override { return OnValueHelper(val); }
	virtual bool OnValue(uint64 val)override { return OnValueHelper(val); }
	virtual bool OnValue(float val) override { return OnValueHelper(val); }
	virtual bool OnValue(double val) override { return OnValueHelper(val); }
	virtual bool OnValue(const StringRef& val)override { return OnValueHelper(val); }
	virtual bool OnValue(const MemoryData& val)override { return OnValueHelper(val); }

	virtual bool OnStructBegin() override
	{
		if (mTargetObject!=nullptr)
		{
			mTargetObject = nullptr;	//set first struct to target object
			return true;	
		}
		LuaStack s(mState.GetState());
		s.NewTable();
		return true;
	}

	virtual bool OnStructEnd()override
	{
		return true;
	}

	virtual bool OnListBegin(byte itemType, uint count)override
	{
		LuaStack s(mState.GetState());
		s.NewTable(count);

		return true;
	}

	virtual bool OnListItemBegin(uint index) override
	{
		return true;
	}

	virtual bool OnListItemEnd(uint index) override
	{
		LuaStack s(mState.GetState());
		s.RawsetAt(index + 1);

		return true;
	}

	virtual bool OnListEnd(uint count) override
	{
		return true;
	}

	virtual bool OnDictionaryBegin(byte keyType, byte valueType, uint count)override
	{
		LuaStack s(mState.GetState());
		s.NewTable(0, count);

		return true;

	}
	virtual bool OnDictionaryItemBegin(uint index) override
	{
		return true;
	}

	virtual bool OnDictionaryItemEnd(uint index) override
	{
		LuaStack s(mState.GetState());
		s.RawSetField();
		return true;
	}

	virtual bool OnDictionaryEnd(uint count) override
	{
		return true;
	}

	virtual bool OnFieldBegin(const StringRef& name, ushort id, byte type)override
	{
		LuaStack s(mState.GetState());
		s.Push(name);

		return true;
	}

	virtual bool OnFieldEnd() override
	{
		//table,key,value
		LuaStack s(mState.GetState());
		s.RawSetField();

		return true;
	}


	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnFieldBegin(name, id, Siren::GetDataType<TObject>::Type);
		OnValue(obj);
		OnFieldEnd();
	}

	template<typename TObject, bool TWithHeader = true>
	typename std::enable_if<!TWithHeader>::type OnField(const StringRef& name, ushort id, const TObject& obj)
	{
		OnValue(obj);
	}

	template<typename TObject>
	void OnStruct(const TObject& obj)
	{
		SirenSchemaSerializer::Visit(*this, obj);
	}


	template<typename T>
	bool OnValueHelper(const T& val)
	{
		LuaStack s(mState.GetState());
		s.Push(val);
		return true;
	}

public:
	LuaRef ToObject()const { return LuaRef::PopFromStack(mState.GetState()); }
private:
	LuaState mState;
	LuaRef mTargetObject;
};


MEDUSA_END;
#endif