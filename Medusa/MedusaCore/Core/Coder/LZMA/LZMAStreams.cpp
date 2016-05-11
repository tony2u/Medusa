// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "LZMAStreams.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

LZMASeqInStream::LZMASeqInStream(const IStream& stream) :mStream(stream)
{
	Read = LZMARead;
}

SRes LZMASeqInStream::LZMARead(void *p, void *buf, size_t *size)
{
	LZMASeqInStream* steam = (LZMASeqInStream*)p;
	return steam->ReadTo(buf, size);
}

SRes LZMASeqInStream::ReadTo(void *buf, size_t *size) const
{
	/* if (input(*size) != 0 && output(*size) == 0) means end_of_stream.
	(output(*size) < input(*size)) is allowed */

	size_t originalSize = *size;
	if (originalSize == 0)
		return SZ_OK;

	MemoryData outData= MemoryData::FromStatic((byte*)buf, *size);
	*size=mStream.ReadDataTo(outData);
	return SZ_OK;
}

LZMASeqOutStream::LZMASeqOutStream(IStream& stream)
	:mStream(stream)
{
	Write = LZMAWrite;
}
size_t LZMASeqOutStream::LZMAWrite(void *p, const void *buf, size_t size)
{
	LZMASeqOutStream* steam = (LZMASeqOutStream*)p;
	return steam->WriteData(buf, size);
}

size_t LZMASeqOutStream::WriteData(const void *buf, size_t size)
{
	/* Returns: result - the number of actually written bytes.
	(result < size) means error */

	auto data= MemoryData::FromStatic((const byte*)buf, size);
	return mStream.WriteData(data);
}


MEDUSA_END;
