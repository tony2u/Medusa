// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"


MEDUSA_BEGIN;


class SirenObject
{
	using ListData = List<SirenObject>;
	using DictionaryData = Dictionary<SirenObject, SirenObject>;
	using FieldDictionary = Dictionary<HeapString, SirenObject>;

	union Data
	{
		bool Bool;
		char Int8;
		byte UInt8;
		short Int16;
		ushort UInt16;
		int32 Int32;
		uint32 UInt32;
		int64 Int64;
		uint64 UInt64;
		float Float;
		double Double;

		MemoryData* Blob;
		HeapString* String;
		ListData* List;
		DictionaryData* Dictionary;
		int Enum;
		FieldDictionary* Fields;
	};
public:
	const static SirenObject Null;
public:
	SirenObject(SirenTypeId type = SirenTypeId::Null) :mType(type) {}
	SirenObject(bool val) :mType(SirenTypeId::Bool) { mData.Bool = val; }
	SirenObject(char val) :mType(SirenTypeId::Int8) { mData.Int8 = val; }
	SirenObject(byte val) :mType(SirenTypeId::UInt8) { mData.UInt8 = val; }
	SirenObject(short val) :mType(SirenTypeId::Int16) { mData.Int16 = val; }
	SirenObject(ushort val) :mType(SirenTypeId::UInt16) { mData.UInt16 = val; }
	SirenObject(int32 val) :mType(SirenTypeId::Int32) { mData.Int32 = val; }
	SirenObject(uint32 val) :mType(SirenTypeId::UInt32) { mData.UInt32 = val; }
	SirenObject(int64 val) :mType(SirenTypeId::Int64) { mData.Int64 = val; }
	SirenObject(uint64 val) :mType(SirenTypeId::UInt64) { mData.UInt64 = val; }
	SirenObject(float val) :mType(SirenTypeId::Float) { mData.Float = val; }
	SirenObject(double val) :mType(SirenTypeId::Double) { mData.Double = val; }
	SirenObject(const MemoryData& val);
	SirenObject(const StringRef& val);
	SirenObject(const char* val);
	SirenObject(const ListData& val);
	SirenObject(const DictionaryData& val);

	~SirenObject(void);

	SirenObject(const SirenObject& other);
	SirenObject& operator=(const SirenObject& other);
	SirenObject(SirenObject&& other);
	SirenObject& operator=(SirenObject&& other);

	bool operator==(const SirenObject& other)const;
	bool operator!=(const SirenObject& other)const;

	bool operator==(std::nullptr_t)const { return IsNull(); }
	bool operator!=(std::nullptr_t)const { return !IsNull(); }
public:
	SirenTypeId Type() const { return mType; }
	intp HashCode()const;

	bool IsNull()const { return mType == SirenTypeId::Null; }
	bool IsBool()const { return mType == SirenTypeId::Bool; }
	bool IsInt8()const { return mType == SirenTypeId::Int8; }
	bool IsUInt8()const { return mType == SirenTypeId::UInt8; }
	bool IsInt16()const { return mType == SirenTypeId::Int16; }
	bool IsUInt16()const { return mType == SirenTypeId::UInt16; }
	bool IsInt32()const { return mType == SirenTypeId::Int32; }
	bool IsUInt32()const { return mType == SirenTypeId::UInt32; }
	bool IsInt64()const { return mType == SirenTypeId::Int64; }
	bool IsUInt64()const { return mType == SirenTypeId::UInt64; }
	bool IsFloat()const { return mType == SirenTypeId::Float; }
	bool IsDouble()const { return mType == SirenTypeId::Double; }
	bool IsString()const { return mType == SirenTypeId::Double; }
	bool IsBlob()const { return mType == SirenTypeId::Blob; }
	bool IsList()const { return mType == SirenTypeId::List; }
	bool IsDictionary()const { return mType == SirenTypeId::Dictionary; }
	bool IsEnum()const { return mType == SirenTypeId::Enum; }
	bool IsStruct()const { return mType == SirenTypeId::Struct; }

	SirenObject& SetNull() { SetType(SirenTypeId::Null); return *this; }
	SirenObject& SetBool(bool val) { SetType(SirenTypeId::Bool); mData.Bool = val; return *this; }
	SirenObject& SetInt8(char val) { SetType(SirenTypeId::Int8); mData.Int8 = val; return *this; }
	SirenObject& SetUint8(byte val) { SetType(SirenTypeId::UInt8); mData.UInt8 = val; return *this; }
	SirenObject& SetInt16(short val) { SetType(SirenTypeId::UInt16); mData.UInt16 = val; return *this; }
	SirenObject& SetUInt16(ushort val) { SetType(SirenTypeId::UInt16); mData.UInt16 = val; return *this; }
	SirenObject& SetInt32(int32 val) { SetType(SirenTypeId::Int32); mData.Int32 = val; return *this; }
	SirenObject& SetUInt32(uint32 val) { SetType(SirenTypeId::UInt32); mData.UInt32 = val; return *this; }
	SirenObject& SetInt64(int64 val) { SetType(SirenTypeId::Int64); mData.Int64 = val; return *this; }
	SirenObject& SetUInt64(uint64 val) { SetType(SirenTypeId::UInt64); mData.UInt64 = val; return *this; }
	SirenObject& SetFloat(float val) { SetType(SirenTypeId::Float); mData.Float = val; return *this; }
	SirenObject& SetDouble(double val) { SetType(SirenTypeId::Double); mData.Double = val; return *this; }
	SirenObject& SetString(const StringRef& val) { SetType(SirenTypeId::String); *mData.String = val; return *this; }
	SirenObject& SetBlob(const MemoryData& val) { SetType(SirenTypeId::String); *mData.Blob = val.Clone(); return *this; }

	SirenObject& SetList() { SetType(SirenTypeId::List); return *this; }
	SirenObject& SetDictionary() { SetType(SirenTypeId::Dictionary); return *this; }
	SirenObject& SetEnum(int32 val) { SetType(SirenTypeId::Enum); mData.Enum = val; return *this; }
	SirenObject& SetStruct() { SetType(SirenTypeId::Struct); return *this; }

	SirenObject& Set(std::nullptr_t) { SetType(SirenTypeId::Null); return *this; }
	SirenObject& Set(bool val) { SetType(SirenTypeId::Bool); mData.Bool = val; return *this; }
	SirenObject& Set(char val) { SetType(SirenTypeId::Int8); mData.Int8 = val; return *this; }
	SirenObject& Set(byte val) { SetType(SirenTypeId::UInt8); mData.UInt8 = val; return *this; }
	SirenObject& Set(short val) { SetType(SirenTypeId::UInt16); mData.UInt16 = val; return *this; }
	SirenObject& Set(ushort val) { SetType(SirenTypeId::UInt16); mData.UInt16 = val; return *this; }
	SirenObject& Set(int32 val) { SetType(SirenTypeId::Int32); mData.Int32 = val; return *this; }
	SirenObject& Set(uint32 val) { SetType(SirenTypeId::UInt32); mData.UInt32 = val; return *this; }
	SirenObject& Set(int64 val) { SetType(SirenTypeId::Int64); mData.Int64 = val; return *this; }
	SirenObject& Set(uint64 val) { SetType(SirenTypeId::UInt64); mData.UInt64 = val; return *this; }
	SirenObject& Set(float val) { SetType(SirenTypeId::Float); mData.Float = val; return *this; }
	SirenObject& Set(double val) { SetType(SirenTypeId::Double); mData.Double = val; return *this; }
	SirenObject& Set(const StringRef& val) { SetType(SirenTypeId::String); *mData.String = val; return *this; }
	SirenObject& Set(const char* val) { SetType(SirenTypeId::String); *mData.String = val; return *this; }
	SirenObject& Set(const MemoryData& val) { SetType(SirenTypeId::Blob); *mData.Blob = val.Clone(); return *this; }

	template<typename T>
	SirenObject& operator=(T val) { return Set(val); }


	bool GetBool()const { AssertType(SirenTypeId::Bool); return mData.Bool; }
	char GetInt8()const { AssertType(SirenTypeId::Int8); return mData.Int8; }
	byte GetUInt8()const { AssertType(SirenTypeId::UInt8); return mData.UInt8; }
	short GetInt16()const { AssertType(SirenTypeId::Int16); return mData.Int16; }
	ushort GetUInt16()const { AssertType(SirenTypeId::UInt16); return mData.UInt16; }
	int32 GetInt32()const { AssertType(SirenTypeId::Int32); return mData.Int32; }
	uint32 GetUInt32()const { AssertType(SirenTypeId::UInt32); return mData.UInt32; }
	int64 GetInt64()const { AssertType(SirenTypeId::Int64); return mData.Int64; }
	uint64 GetUInt64()const { AssertType(SirenTypeId::UInt64); return mData.UInt64; }
	float GetFloat()const { AssertType(SirenTypeId::Float); return mData.Float; }
	double GetDouble()const { AssertType(SirenTypeId::Double); return mData.Double; }
	StringRef GetString()const { AssertType(SirenTypeId::String); return *mData.String; }
	const MemoryData& GetBlob()const { AssertType(SirenTypeId::Blob); return *mData.Blob; }
	const ListData& GetList()const { AssertType(SirenTypeId::List); return *mData.List; }
	const DictionaryData& GetDictionary()const { AssertType(SirenTypeId::Dictionary); return *mData.Dictionary; }
	int32 GetEnum()const { AssertType(SirenTypeId::Enum); return mData.Enum; }
	const FieldDictionary& GetStruct()const { AssertType(SirenTypeId::Struct); return *mData.Fields; }

	template<typename T>
	T Get()const;

	template<> bool Get()const { AssertType(SirenTypeId::Bool); return mData.Bool; }
	template<> char Get()const { AssertType(SirenTypeId::Int8); return mData.Int8; }
	template<> byte Get()const { AssertType(SirenTypeId::UInt8); return mData.UInt8; }
	template<> short Get()const { AssertType(SirenTypeId::Int16); return mData.Int16; }
	template<> ushort Get()const { AssertType(SirenTypeId::UInt16); return mData.UInt16; }
	template<> int32 Get()const { AssertType(SirenTypeId::Int32); return mData.Int32; }
	template<> uint32 Get()const { AssertType(SirenTypeId::UInt32); return mData.UInt32; }
	template<> int64 Get()const { AssertType(SirenTypeId::Int64); return mData.Int64; }
	template<> uint64 Get()const { AssertType(SirenTypeId::UInt64); return mData.UInt64; }
	template<> float Get()const { AssertType(SirenTypeId::Float); return mData.Float; }
	template<> double Get()const { AssertType(SirenTypeId::Double); return mData.Double; }
	template<> StringRef Get()const { AssertType(SirenTypeId::String); return *mData.String; }
	template<> MemoryData Get()const { AssertType(SirenTypeId::Blob); return *mData.Blob; }

	bool& MutableBool() { AssertType(SirenTypeId::Bool); return mData.Bool; }
	char& MutableInt8() { AssertType(SirenTypeId::Int8); return mData.Int8; }
	byte& MutableUInt8() { AssertType(SirenTypeId::UInt8); return mData.UInt8; }
	short& MutableInt16() { AssertType(SirenTypeId::Int16); return mData.Int16; }
	ushort& MutableUInt16() { AssertType(SirenTypeId::UInt16); return mData.UInt16; }
	int32& MutableInt32() { AssertType(SirenTypeId::Int32); return mData.Int32; }
	uint32& MutableUInt32() { AssertType(SirenTypeId::UInt32); return mData.UInt32; }
	int64& MutableInt64() { AssertType(SirenTypeId::Int64); return mData.Int64; }
	uint64& MutableUInt64() { AssertType(SirenTypeId::UInt64); return mData.UInt64; }
	float& MutableFloat() { AssertType(SirenTypeId::Float); return mData.Float; }
	double& MutableDouble() { AssertType(SirenTypeId::Double); return mData.Double; }
	HeapString& MutableString() { AssertType(SirenTypeId::String); return *mData.String; }
	MemoryData& MutableBlob() { AssertType(SirenTypeId::Blob); return *mData.Blob; }
	ListData& MutableList() { AssertType(SirenTypeId::List); return *mData.List; }
	DictionaryData& MutableDictionary() { AssertType(SirenTypeId::Dictionary); return *mData.Dictionary; }
	int32& MutableEnum() { AssertType(SirenTypeId::Enum); return mData.Enum; }

	bool HasValue(const SirenObject& defaultValue)const;
	void SetValue(const StringRef& defaultValue);

	void SetTypeAndValue(SirenTypeId type,const StringRef& val);



	size_t Count()const;
	//list
	const SirenObject& At(uint index)const { AssertType(SirenTypeId::List); return (*mData.List)[index]; }
	SirenObject& MutableAt(uint index) { AssertType(SirenTypeId::List); return (*mData.List)[index]; }
	void Add(const SirenObject& val) { AssertType(SirenTypeId::List); return mData.List->Add(val); }

	template<typename T>
	void Add(T val) { AssertType(SirenTypeId::List); return mData.List->EmplaceBack(val); }

	//dictionary
	void Add(const SirenObject& key, const SirenObject& val) { AssertType(SirenTypeId::Dictionary); return mData.Dictionary->Add(key, val); }
	SirenObject GetValue(const SirenObject& key)const { AssertType(SirenTypeId::Dictionary); return mData.Dictionary->Get(key); }
	SirenObject GetField(const StringRef& name) const { AssertType(SirenTypeId::Struct); return mData.Fields->Get(name); }
	SirenObject* TryGetField(const StringRef& name) const { AssertType(SirenTypeId::Struct); return mData.Fields->TryGet(name); }
	SirenObject& NewField(const StringRef& name) { AssertType(SirenTypeId::Struct); return mData.Fields->NewAdd(name); }
	SirenObject& NewStruct(const StringRef& name) { return NewField(name).SetStruct(); }

	template<typename T>
	SirenObject& AddEnum(const StringRef& name, T val) { return NewField(name).SetEnum((int32)val); }

	template<typename T>
	SirenObject& AddField(const StringRef& name, T val) { NewField(name).Set(val); return *this; }

	template<typename T>
	SirenObject& AddField(const char* name, T val) { NewField(name).Set(val); return *this; }

	HeapString Print()const;
	void SetType(SirenTypeId val);
private:
	void SetData(const Data& val) { mData = val; }
	void Destroy();
	void ClearData();
	void AssertType(SirenTypeId type)const;

	void PrintHelper(HeapString& str, uintp depth = 0, bool withPrefix = true)const;

protected:
	SirenTypeId mType;
	Data mData;

};

MEDUSA_END;
