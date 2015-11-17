// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ICoder.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

size_t ICoder::Code(const MemoryByteData& input, MemoryByteData& output) const
{
	return OnCode(input, output);
}

size_t ICoder::Code(IStream& input, IStream& output) const
{
	if (&input == &output)
	{
		Log::AssertFailed("Code cannot accept one stream to be both input with output.");
		return 0;
	}

	CoderFlags flags = Flags();
	if (input.IsPtrAvailable() &&MEDUSA_HAS_FLAG(flags, CoderFlags::InPlace))
	{
		auto data = input.ReadToEnd(DataReadingMode::DirectMove);
		RETURN_ZERO_IF_EMPTY(data);
		size_t count = OnCode(data, data);
		data.ForceSetSize(count);
		return output.WriteData(data, DataReadingMode::DirectMove);
	}

	return Code((const IStream&)input, output);	//refer to const version
}

size_t ICoder::Code(const IStream& input, IStream& output) const
{
	if (&input == &output)
	{
		Log::AssertFailed("Code cannot accept one stream to be both input with output.");
		return 0;
	}

	CoderFlags flags = Flags();
	uintp resultSize = GuessResultSize(input);
	if (resultSize == 0)
	{
		return OnCode(input, output);
	}

	if (MEDUSA_HAS_FLAG(flags, CoderFlags::Block))
	{
		auto data = input.ReadToEnd(DataReadingMode::DirectMove);
		RETURN_ZERO_IF_EMPTY(data);

		if (output.IsPtrAvailable())
		{
			RETURN_FALSE_IF_FALSE(output.ReserveLeftSize(resultSize));
			MemoryByteData destData = MemoryByteData::FromStatic(output.MutablePtr(), resultSize);
			size_t count = OnCode(data, destData);
			output.Skip(count);
			return count;
		}
		else
		{
			//create a temp copy
			MemoryByteData destData = MemoryByteData::Alloc(resultSize);
			size_t count = OnCode(data, destData);
			destData.ForceSetSize(count);
			return output.WriteData(destData);
		}
	}

	if (MEDUSA_HAS_FLAG(flags, CoderFlags::Streaming))
	{
		return OnCode(input, output);
	}

	return 0;
}

MemoryByteData ICoder::Code(const MemoryByteData& input) const
{
	const MemoryStream inputStream(input);
	MemoryStream outputStream;
	Code(inputStream, outputStream);
	return outputStream.CurrentBuffer();
}

MemoryByteData ICoder::Code(MemoryByteData& input) const
{
	CoderFlags flags = Flags();
	if (MEDUSA_HAS_FLAG(flags, CoderFlags::InPlace))
	{
		OnCode(input, input);
		return input;
	}

	MemoryStream inputStream(input);
	MemoryStream outputStream;
	Code(inputStream, outputStream);
	return outputStream.CurrentBuffer();
}

MemoryByteData ICoder::Code(const StringRef& input) const
{
	const MemoryByteData inputData = MemoryByteData::FromStatic((const byte*)input.c_str(), input.Length());
	return Code(inputData);
}

MemoryByteData ICoder::Code(HeapString& input) const
{
	MemoryByteData inputData = MemoryByteData::FromStatic((const byte*)input.c_str(), input.Length());
	return Code(inputData);
}


MEDUSA_END;

