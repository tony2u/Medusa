// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Log/Log.h"
#include "Core/Compile/TypeTraits.h"
#include "SirenMacro.h"
#include "Core/Siren/Schema/SirenFieldInfo.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"

#include "Core/Siren/SirenTraits.h"
#include "Core/Siren/Code/Json/SirenJsonWriter.h"
#include "Core/Siren/Code/Json/SirenJsonReader.h"

#include "Core/Siren/Code/Binary/SirenCompactBinaryWriter.h"
#include "Core/Siren/Code/Binary/SirenCompactBinaryReader.h"

#include "Core/Siren/Code/Binary/SirenFastBinaryWriter.h"
#include "Core/Siren/Code/Binary/SirenFastBinaryReader.h"

#include "Core/Siren/Code/Lua/SirenLuaReader.h"
#include "Core/Siren/Code/Lua/SirenLuaWriter.h"

#include "Core/Siren/Code/Sql/SirenSqlTextReader.h"
#include "Core/Siren/Code/Sql/SirenSqlTextWriter.h"

#include "Core/Siren/Schema/SirenMachine.h"

#include "Core/Siren/Serialization/SirenSchemaDeserializer.h"
#include "Core/Siren/Serialization/SirenSchemaSerializer.h"
#include "Core/IO/Stream/StringStream.h"

/*
All field sorted asdending order by Id
Current Id == readed Id		match
Current Id < readed Id		miss
Current Id > readed Id		unknown filed

backward compatible(use new protocol to read old data):
New field:need set to optional
delete field:need skip
reorder fields:need field unique id

forward compatible(use old protocol to read new data):
New field:need skip
delete field:need set to optional
reorder fields:need field unique id
*/

MEDUSA_BEGIN;
namespace Siren
{
	MemoryData Serialize(const SirenObject& obj, const ISirenType& type, SirenCoderType coder = SirenCoderType::Compact);
	SirenObject Deserialize(const MemoryData& data, const ISirenType& type, SirenCoderType coder = SirenCoderType::Compact);

#ifdef MEDUSA_SCRIPT
	HeapString SerializeScript(const ScriptObject& obj, const ISirenType& type, SirenCoderType coder = SirenCoderType::Compact);
	ScriptObject DeserializeScript(ScriptState& state, const StringRef& data, const ISirenType& type, SirenCoderType coder = SirenCoderType::Compact);
	bool DeserializeScriptTo(ScriptObject& obj, const StringRef& data, const ISirenType& type, SirenCoderType coder = SirenCoderType::Compact);
#endif


#ifdef MEDUSA_LUA
	bool SerializeLua(const SirenObject& obj, const ISirenType& type, LuaState& state);
	SirenObject DeserializeLua(LuaState& state, const ISirenType& type);
#endif


	template <class TWriter, typename T, bool TIsForceWriteDefault = false>
	static MemoryData Serialize(const T& obj)
	{
		MemoryStream stream;
		TWriter writer(stream);
		if (SirenSchemaSerializer<TIsForceWriteDefault>::Visit(writer, obj))
		{
			return stream.CurrentBuffer();
		}
		return MemoryData::Empty;
	}

	template <class TReader, typename T>
	static bool DeserializeTo(const MemoryData& data, T& outObj)
	{
		MemoryStream stream(data);
		TReader reader(stream);
		return SirenSchemaDeserializer::Visit(reader, outObj);
	}

	template <class TSizeCounter, typename T, bool TIsForceWriteDefault = false>
	static MemoryData ByteSize(const T& obj)
	{
		TSizeCounter counter;
		SirenSchemaSerializer<TIsForceWriteDefault>::Visit(counter, obj);
		return counter.Size();
	}


	//////////////////////////////////////////////////////////////////////////

	template <typename T>
	static MemoryData SerializeBinary(const T& obj)
	{
		return Serialize<SirenCompactBinaryWriter, T>(obj);
	}

	template <typename T>
	static bool DeserializeBinaryTo(const MemoryData& data, T& outObj)
	{
		return DeserializeTo<SirenCompactBinaryReader, T>(data, outObj);
	}


	template <typename T, bool TIsForceWriteDefault = false>
	static HeapString SerializeJson(const T& obj)
	{
		HeapString str;
		StringStream stream(str);
		SirenJsonWriter writer(stream);
		if (SirenSchemaSerializer<TIsForceWriteDefault>::Visit(writer, obj))
		{
			return str;
		}
		return HeapString::Empty;
	}

	template <typename T>
	static bool DeserializeJsonTo(const StringRef& str, T& outObj)
	{
	
		return DeserializeTo<SirenJsonReader, T>(MemoryData::FromStatic((byte*)str.c_str(),str.Length()), outObj);
	}

#ifdef MEDUSA_SQL
	template <typename T, bool TIsForceWriteDefault = true>
	static HeapString SerializeSqlText(const T& obj)
	{
		HeapString str;
		StringStream stream(str);
		SirenSqlTextWriter writer(stream);
		if (SirenSchemaSerializer<TIsForceWriteDefault>::Visit(writer, obj))
		{
			return str;
		}
		return HeapString::Empty;
	}

	template <typename T>
	static bool DeserializeSqlTextTo(MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount, T& outObj)
	{
		SirenSqlTextReader reader(row, rowLengths,fields, fieldCount, Siren::GetFieldCount<T>::value);
		return SirenSchemaDeserializer::Visit(reader, outObj);
	}

#endif

#ifdef MEDUSA_LUA

	template <typename T, bool TIsForceWriteDefault = false>
	static bool SerializeLua(const T& obj, LuaState& state)
	{
		SirenLuaWriter writer(state);
		return SirenSchemaSerializer<TIsForceWriteDefault>::Visit(writer, obj);
	}

	template <typename T>
	static bool DeserializeLuaTo(LuaState& state, T& outObj)
	{
		SirenLuaReader reader(state);
		return SirenSchemaDeserializer::Visit(reader, outObj);
	}
#endif

	template <typename T>
	static MemoryData Serialize(const T& obj, SirenCoderType protocol)
	{
		switch (protocol)
		{
		case SirenCoderType::Compact:
			return Serialize<SirenCompactBinaryWriter, T>(obj);
		case SirenCoderType::Fast:
			return Serialize<SirenFastBinaryWriter, T>(obj);
		case SirenCoderType::Json:
			return Serialize<SirenJsonWriter, T>(obj);
#ifdef MEDUSA_SQL
		case SirenCoderType::SqlText:
			return Serialize<SirenSqlTextWriter, T>(obj);
#endif
		}
		return MemoryData::Empty;
	}

	template <typename T>
	static bool DeserializeTo(const MemoryData& data, T& outObj, SirenCoderType protocol)
	{
		switch (protocol)
		{
		case SirenCoderType::Compact:
			return DeserializeTo<SirenCompactBinaryReader, T>(data, outObj);
		case SirenCoderType::Fast:
			return DeserializeTo<SirenFastBinaryReader, T>(data, outObj);
		case SirenCoderType::Json:
			return DeserializeTo<SirenJsonReader, T>(data, outObj);
		}
		return false;
	}


	namespace internal
	{
		MemoryData ReadAllData(const FileIdRef& fileId);
	}

	template<typename T>
	static bool LoadProto(T& outItem, const FileIdRef& fileId, SirenCoderType protocol = SirenCoderType::Compact)
	{
		MemoryData data = internal::ReadAllData(fileId);

		if (data.IsNull())
		{
			return false;
		}
		bool result = Siren::DeserializeTo(data, outItem, protocol);

		return result;
	}




}

MEDUSA_END;