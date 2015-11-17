// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/LZMA/LZMAEncoder.h"
#include "Core/Coder/CoderFactory.h"
#include "CoreLib/Common/Lzma/LzmaEnc.h"
#include "Core/IO/Stream/IStream.h"
#include "LZMAStreams.h"

MEDUSA_BEGIN;



LZMAEncoder::LZMAEncoder(const IEventArg& e) :ICoder(e)
{
}

LZMAEncoder::~LZMAEncoder()
{

}

static void* LZMAAlloc(void *p, size_t size)
{
	return malloc(size);
}

static void LZMAFree(void *p, void *address)
{
	SAFE_FREE(address);
}


size_t LZMAEncoder::GuessResultSize(const IStream& input) const
{
	return 0;
}

size_t LZMAEncoder::OnCode(const IStream& input, IStream& output) const
{
	CLzmaEncProps props;
	SRes res;
	size_t resultSize = 0;
	uintp oldPos = output.Position();
	LzmaEncProps_Init(&props);
	props.level = 5;
	props.dictSize = 1 << 24;
	props.lc = 3;
	props.lp = 0;
	props.pb = 2;
	props.fb = 32;
	props.numThreads = 1;	//single thread

	ISzAlloc myAlloc;
	myAlloc.Alloc = LZMAAlloc;
	myAlloc.Free = LZMAFree;
	CLzmaEncHandle enc = LzmaEnc_Create(&myAlloc);
	res = LzmaEnc_SetProps(enc, &props);

	if (res == SZ_OK)
	{
		byte header[LZMA_PROPS_SIZE + 8];
		size_t headerSize = LZMA_PROPS_SIZE;
		int i;
		uint64 dataSize = input.LeftLength();
		res = LzmaEnc_WriteProperties(enc, header, &headerSize);
		for (i = 0; i < 8; i++)
			header[LZMA_PROPS_SIZE+i] = (Byte)(dataSize >> (8 * i));

		output.WriteData(MemoryByteData::FromStatic(header));

		LZMASeqInStream inStream(input);
		LZMASeqOutStream outStream(output);
		res = LzmaEnc_Encode(enc, &outStream, &inStream, nullptr, &myAlloc, &myAlloc);
		if (res==SZ_OK)
		{
			resultSize = output.Position()- oldPos;
		}
		else
		{
			resultSize = 0;
		}
	}

	LzmaEnc_Destroy(enc, &myAlloc, &myAlloc);
	return resultSize;
}

MEDUSA_END;
