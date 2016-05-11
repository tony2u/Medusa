// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ICoder.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

size_t ICoder::Code(const MemoryData& input, MemoryData& output) const
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
	if (input.IsPtrAvailable() &&MEDUSA_FLAG_HAS(flags, CoderFlags::InPlace))
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

	if (MEDUSA_FLAG_HAS(flags, CoderFlags::Block))
	{
		auto data = input.ReadToEnd(DataReadingMode::DirectMove);
		RETURN_ZERO_IF_EMPTY(data);

		if (output.IsPtrAvailable())
		{
			RETURN_FALSE_IF_FALSE(output.ReserveLeftSize(resultSize));
			MemoryData destData = MemoryData::FromStatic(output.MutablePtr(), resultSize);
			size_t count = OnCode(data, destData);
			output.Skip(count);
			return count;
		}
		else
		{
			//create a temp copy
			MemoryData destData = MemoryData::Alloc(resultSize);
			size_t count = OnCode(data, destData);
			destData.ForceSetSize(count);
			return output.WriteData(destData);
		}
	}

	if (MEDUSA_FLAG_HAS(flags, CoderFlags::Streaming))
	{
		return OnCode(input, output);
	}

	return 0;
}

MemoryData ICoder::Code(const MemoryData& input) const
{
	const MemoryStream inputStream(input);
	MemoryStream outputStream;
	Code(inputStream, outputStream);
	return outputStream.CurrentBuffer();
}

MemoryData ICoder::Code(MemoryData& input) const
{
	CoderFlags flags = Flags();
	if (MEDUSA_FLAG_HAS(flags, CoderFlags::InPlace))
	{
		OnCode(input, input);
		return input;
	}

	MemoryStream inputStream(input);
	MemoryStream outputStream;
	Code(inputStream, outputStream);
	return outputStream.CurrentBuffer();
}

MemoryData ICoder::Code(const StringRef& input) const
{
	const MemoryData inputData = MemoryData::FromStatic((const byte*)input.c_str(), input.Length());
	return Code(inputData);
}

MemoryData ICoder::Code(HeapString& input) const
{
	MemoryData inputData = MemoryData::FromStatic((const byte*)input.c_str(), input.Length());
	return Code(inputData);
}


MEDUSA_END;

