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
#include "Core/Siren/Reflection/PropertyInfo.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"

#include "Core/Siren/SirenTraits.h"
#include "Core/Siren/Protocol/Json/JsonWriter.h"
#include "Core/Siren/Protocol/Json/JsonReader.h"

#include "Core/Siren/Protocol/Binary/CompactBinaryWriter.h"
#include "Core/Siren/Protocol/Binary/CompactBinaryReader.h"

#include "Core/Siren/Protocol/Binary/FastBinaryWriter.h"
#include "Core/Siren/Protocol/Binary/FastBinaryReader.h"

/*
All field sorted asdending order by Id
Current Id == readed Id		match
Current Id < readed Id		miss 
Current Id > readed Id		unknown filed

backward compatiable(use new protocol to read old data):
New field:need set to optional
delete field:need skip
reorder fields:need field unique id

forward compatiable(use old protocol to read new data):
New field:need skip
delete field:need set to optional
reorder fields:need field unique id
*/

namespace Medusa
{
	namespace Siren
	{
		
		

		template <template<typename TStream> class TWriter, typename T>
		static MemoryByteData Serialize(const T& obj)
		{
			MemoryStream stream;
			TWriter<MemoryStream> writer(stream);
			if (writer.Run(obj))
			{
				return stream.CurrentBuffer();
			}
			return MemoryByteData::Empty;
		}

		template <template<typename TStream> class TReader, typename T>
		static bool DeserializeTo(const MemoryByteData& data, T& outObj)
		{
			MemoryStream stream(data);
			TReader<MemoryStream> reader(stream);
			return reader.Run(outObj);
		}

		template <template<typename TStream> class TWriter, typename T>
		static MemoryByteData ByteSize(const T& obj)
		{
			typename TWriter<MemoryStream>::SizeCounter counter;
			return counter.Run(obj);
		}


		//////////////////////////////////////////////////////////////////////////

		template <typename T>
		static MemoryByteData SerializeBinary(const T& obj)
		{
			MemoryStream stream;
			CompactBinaryWriter<MemoryStream> writer(stream);
			if (writer.Run(obj))
			{
				return stream.CurrentBuffer();
			}
			return MemoryByteData::Empty;
		}

		template <typename T>
		static bool DeserializeBinaryTo(const MemoryByteData& data, T& outObj)
		{
			MemoryStream stream(data);
			CompactBinaryReader<MemoryStream> reader(stream);
			return reader.Run(outObj);
		}


		template <typename T>
		static void SerializeJson(const T& obj, HeapString& outStr)
		{
			JsonWriter<HeapString> writer(outStr);
			writer.Run(obj);
		}

		template <typename T>
		static bool DeserializeJsonTo(const StringRef& str, T& outObj)
		{
			MemoryStream stream(str.ToData().Cast<byte>());
			JsonReader<MemoryStream> reader(stream);
			return reader.Run(outObj);
		}

		template <typename T>
		static MemoryByteData Serialize(const T& obj, SirenProtocol protocol)
		{
			switch (protocol)
			{
				case SirenProtocol::Compact:
				{
					MemoryStream stream;
					CompactBinaryWriter<MemoryStream> writer(stream);
					if (writer.Run(obj))
					{
						return stream.CurrentBuffer();
					}
					return MemoryByteData::Empty;
				}
				case SirenProtocol::Fast:
				{
					MemoryStream stream;
					FastBinaryWriter<MemoryStream> writer(stream);
					if (writer.Run(obj))
					{
						return stream.CurrentBuffer();
					}
					return MemoryByteData::Empty;
				}
				case SirenProtocol::Json:
				{
					MemoryStream stream;
					JsonWriter<MemoryStream> writer(stream);
					if (writer.Run(obj))
					{
						return stream.CurrentBuffer();
					}
					return MemoryByteData::Empty;
				}
			}

			return MemoryByteData::Empty;
		}

		template <typename T>
		static bool DeserializeTo(const MemoryByteData& data, T& outObj, SirenProtocol protocol)
		{
			switch (protocol)
			{
				case SirenProtocol::Compact:
				{
					MemoryStream stream(data);
					CompactBinaryReader<MemoryStream> reader(stream);
					return reader.Run(outObj);
				}
				case SirenProtocol::Fast:
				{
					MemoryStream stream(data);
					FastBinaryReader<MemoryStream> reader(stream);
					return reader.Run(outObj);
				}
				case SirenProtocol::Json:
				{
					MemoryStream stream(data);
					JsonReader<MemoryStream> reader(stream);
					return reader.Run(outObj);
				}
			}
			return false;
		}
		

		namespace internal
		{
			MemoryByteData ReadAllData(const FileIdRef& fileId);
		}

		template<typename T>
		static bool LoadProto(T& outItem, const FileIdRef& fileId, SirenProtocol protocol = SirenProtocol::Compact)
		{
			MemoryByteData data = internal::ReadAllData(fileId);

			if (data.IsNull())
			{
				return false;
			}
			bool result = Siren::DeserializeTo(data, outItem, protocol);

			return result;
		}

	


	}
}

