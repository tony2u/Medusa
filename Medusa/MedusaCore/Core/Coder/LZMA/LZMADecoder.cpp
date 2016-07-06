// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LZMA
#include "Core/Coder/LZMA/LZMADecoder.h"
#include "Core/Coder/CoderFactory.h"
#include "CoreLib/Common/Lzma/LzmaDec.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

LZMADecoder::LZMADecoder(const IEventArg& e) :ICoder(e)
{
}

LZMADecoder::~LZMADecoder()
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



size_t LZMADecoder::GuessResultSize(const IStream& input) const
{
	uintp pos = input.Position();
	auto buffer = input.ReadData(LZMA_PROPS_SIZE + 8);
	const byte* inBuffer = buffer.Data();

	ISzAlloc myAlloc;
	myAlloc.Alloc = LZMAAlloc;
	myAlloc.Free = LZMAFree;

	CLzmaDec p;
	SRes res;
	

	LzmaDec_Construct(&p);

	res = LzmaDec_AllocateProbs(&p, inBuffer, LZMA_PROPS_SIZE, &myAlloc);

	uint64 fileSize = 0;
	for (int i = 0; i < 8; i++)
		fileSize |= ((uint64)inBuffer[LZMA_PROPS_SIZE + i]) << (8 * i);

	LzmaDec_FreeProbs(&p, &myAlloc);
	input.SetPosition(pos);

	return (size_t)fileSize;
}


size_t LZMADecoder::OnCode(const MemoryData& input, MemoryData& output) const
{
	RETURN_ZERO_IF_EMPTY(input);
	const byte* inBuffer = input.Data();
	size_t inSize = input.Size();

	ELzmaStatus outStatus;

	ISzAlloc myAlloc;
	myAlloc.Alloc = LZMAAlloc;
	myAlloc.Free = LZMAFree;

	CLzmaDec p;
	SRes res;
	
	LzmaDec_Construct(&p);

	res = LzmaDec_AllocateProbs(&p, inBuffer, LZMA_PROPS_SIZE, &myAlloc);

	uint64 fileSize = 0;
	for (int i = 0; i < 8; i++)
		fileSize |= ((uint64)inBuffer[LZMA_PROPS_SIZE + i]) << (8 * i);

	if (output.Size()<(size_t)fileSize)
	{
		Log::AssertFailedFormat("output size:{} < expected size{}", output.Size(), fileSize);
		LzmaDec_FreeProbs(&p, &myAlloc);
		return 0;
	}

	LzmaDec_Init(&p);

	p.dic = output.MutableData();
	p.dicBufSize = (size_t)fileSize;

	size_t outSize = inSize - 13;
	res = LzmaDec_DecodeToDic(&p, (size_t)fileSize, inBuffer + 13, &outSize, LZMA_FINISH_ANY, &outStatus);

	if (res == SZ_OK && outStatus == LZMA_STATUS_NEEDS_MORE_INPUT)
		res = SZ_ERROR_INPUT_EOF;

	LzmaDec_FreeProbs(&p, &myAlloc);
	return (size_t)fileSize;
}

MEDUSA_END;

#endif
