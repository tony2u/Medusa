// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Siren.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Stream/StringStream.h"
#include "Core/Siren/Serialization/SirenObjectSerializer.h"
#include "Core/Siren/Serialization/SirenObjectDeserializer.h"
#include "Core/Siren/SirenObject.h"
#include "Core/Siren/Serialization/SirenReaderWriter.h"

MEDUSA_BEGIN;

namespace Siren
{
	namespace internal
	{
		MemoryData ReadAllData(const FileIdRef& fileId)
		{
			return FileSystem::Instance().ReadAllData(fileId);
		}

	}

	MemoryData Serialize(const SirenObject& obj, const ISirenType& type, SirenCoderType coder/*=SirenCoderType::Compact*/)
	{
		switch (coder)
		{
		case SirenCoderType::Compact:
		{
			MemoryStream stream;
			SirenCompactBinaryWriter writer(stream);
			SirenObjectSerializer serializer(writer);
			if (serializer.Serialize(obj, type))
			{
				return stream.CurrentBuffer();
			}
			return MemoryData::Empty;
		}
		case SirenCoderType::Fast:
		{
			MemoryStream stream;
			SirenFastBinaryWriter writer(stream);
			SirenObjectSerializer serializer(writer);
			if (serializer.Serialize(obj, type))
			{
				return stream.CurrentBuffer();
			}

			return MemoryData::Empty;
		}
		case SirenCoderType::Json:
		{
			MemoryStream stream;
			SirenJsonWriter writer(stream);
			SirenObjectSerializer serializer(writer);
			if (serializer.Serialize(obj, type))
			{
				return stream.CurrentBuffer();
			}

			return MemoryData::Empty;
		}
#ifdef MEDUSA_SQL
		case SirenCoderType::SqlText:
		{
			MemoryStream stream;
			SirenSqlTextWriter writer(stream);
			SirenObjectSerializer serializer(writer);
			if (serializer.Serialize(obj, type))
			{
				return stream.CurrentBuffer();
			}

			return MemoryData::Empty;
		}
#endif

		}

		return MemoryData::Empty;
	}

	SirenObject Deserialize(const MemoryData& data, const ISirenType& type, SirenCoderType coder /*= SirenCoderType::Compact*/)
	{
		switch (coder)
		{
		case SirenCoderType::Compact:
		{
			SirenObject obj;
			MemoryStream stream(data);
			SirenCompactBinaryReader reader(stream);
			SirenObjectDeserializer deserializer(reader);
			if (deserializer.Deserialize(obj, type))
			{
				return obj;
			}

			return SirenObject::Null;
		}
		case SirenCoderType::Fast:
		{
			SirenObject obj;
			MemoryStream stream(data);
			SirenFastBinaryReader reader(stream);
			SirenObjectDeserializer deserializer(reader);
			if (deserializer.Deserialize(obj, type))
			{
				return obj;
			}
			return SirenObject::Null;

		}
		case SirenCoderType::Json:
		{
			SirenObject obj;
			MemoryStream stream(data);
			SirenJsonReader reader(stream);
			SirenObjectDeserializer deserializer(reader);
			if (deserializer.Deserialize(obj, type))
			{
				return obj;
			}
			return SirenObject::Null;
		}

		}
		return SirenObject::Null;

	}

#ifdef MEDUSA_SCRIPT
	HeapString SerializeScript(const ScriptObject& obj, const ISirenType& type, SirenCoderType coder/* = SirenCoderType::Compact*/)
	{

#ifdef MEDUSA_LUA
		SirenLuaReader reader(obj.State());
#endif

		switch (coder)
		{
		case SirenCoderType::Compact:
		{
			StringStream stream;
			SirenCompactBinaryWriter writer(stream);
			SirenReaderWriter rw(reader, writer);
			if (rw.Run(type))
			{
				return stream.CurrentBuffer();
			}
			return HeapString::Empty;
		}
		case SirenCoderType::Fast:
		{
			StringStream stream;
			SirenFastBinaryWriter writer(stream);
			SirenReaderWriter rw(reader, writer);
			if (rw.Run(type))
			{
				return stream.CurrentBuffer();
			}

			return HeapString::Empty;
		}
		case SirenCoderType::Json:
		{
			StringStream stream;
			SirenJsonWriter writer(stream);
			SirenReaderWriter rw(reader, writer);
			if (rw.Run(type))
			{
				return stream.CurrentBuffer();
			}

			return HeapString::Empty;
		}
		}

		return HeapString::Empty;
	}
	ScriptObject DeserializeScript(ScriptState& state, const StringRef& data, const ISirenType& type, SirenCoderType coder/* = SirenCoderType::Compact*/)
	{
#ifdef MEDUSA_LUA
		SirenLuaWriter writer(state.GetState());
#endif

		switch (coder)
		{
		case SirenCoderType::Compact:
		{
			StringStream stream(data);
			SirenCompactBinaryReader reader(stream);
			SirenReaderWriter rw(reader, writer);
			if (rw.Run(type))
			{
				return writer.ToObject();
			}

			return nullptr;
		}
		case SirenCoderType::Fast:
		{
			StringStream stream(data);
			SirenFastBinaryReader reader(stream);
			SirenReaderWriter rw(reader, writer);
			if (rw.Run(type))
			{
				return writer.ToObject();
			}
			return nullptr;

		}
		case SirenCoderType::Json:
		{
			StringStream stream(data);
			SirenJsonReader reader(stream);
			SirenReaderWriter rw(reader, writer);
			if (rw.Run(type))
			{
				return writer.ToObject();
			}
			return nullptr;
		}
		}
		return nullptr;
	}


	bool DeserializeScriptTo(ScriptObject& obj, const StringRef& data, const ISirenType& type, SirenCoderType coder /*= SirenCoderType::Compact*/)
	{
#ifdef MEDUSA_LUA
		SirenLuaWriter writer(obj);
#endif

		switch (coder)
		{
		case SirenCoderType::Compact:
		{
			StringStream stream(data);
			SirenCompactBinaryReader reader(stream);
			SirenReaderWriter rw(reader, writer);
			return rw.Run(type);
		}
		case SirenCoderType::Fast:
		{
			StringStream stream(data);
			SirenFastBinaryReader reader(stream);
			SirenReaderWriter rw(reader, writer);
			return rw.Run(type);

		}
		case SirenCoderType::Json:
		{
			StringStream stream(data);
			SirenJsonReader reader(stream);
			SirenReaderWriter rw(reader, writer);
			return rw.Run(type);
		}
		}
		return false;
	}


#endif


#ifdef MEDUSA_LUA

	bool SerializeLua(const SirenObject& obj, const ISirenType& type, LuaState& state)
	{
		SirenLuaWriter writer(state.GetState());
		SirenObjectSerializer serializer(writer);
		return serializer.Serialize(obj, type);
	}

	SirenObject DeserializeLua(LuaState& state, const ISirenType& type)
	{
		SirenObject obj;
		SirenLuaReader reader(state.GetState());
		SirenObjectDeserializer deserializer(reader);
		if (deserializer.Deserialize(obj, type))
		{
			return obj;
		}
		return SirenObject::Null;
	}
#endif

}
MEDUSA_END;

