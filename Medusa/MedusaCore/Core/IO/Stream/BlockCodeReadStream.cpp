// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/BlockCodeReadStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Storage/FileEntry.h"

MEDUSA_BEGIN;


BlockCodeReadStream::BlockCodeReadStream(const Share<const IStream>& stream, uint32 blockSize, const CoderChain& coderChain,const FileEntry& fileEntry)
	: BlockReadStream(stream,blockSize),
	mFileEntry(&fileEntry),
	mCoderChain(&coderChain)
{
}


BlockCodeReadStream::BlockCodeReadStream(BlockCodeReadStream&& other)
	:BlockReadStream(std::move(other)),
	mFileEntry(other.mFileEntry),
	mCoderChain(std::move(other.mCoderChain))
{
	other.mFileEntry = nullptr;
	other.mCoderChain = nullptr;
}

BlockCodeReadStream& BlockCodeReadStream::operator=(BlockCodeReadStream&& other)
{
	if (this != &other)
	{
		Close();
		BlockReadStream::operator=(std::move(other));

		mFileEntry = other.mFileEntry;
		mCoderChain = other.mCoderChain;

		other.mFileEntry = nullptr;
		other.mCoderChain = nullptr;
	}
	return *this;
}



BlockCodeReadStream::~BlockCodeReadStream(void)
{
	Close();
}


uintp BlockCodeReadStream::Length() const
{
	return mFileEntry->OriginalSize();
}

size_t BlockCodeReadStream::LoadBlockTo(uint blockIndex, MemoryStream& output)const
{
	size_t blockCount = mFileEntry->CoderOffsetsCount();
	if (blockIndex < blockCount)
	{
		uint nextOffset = mFileEntry->CoderOffsets()[blockIndex];
		uint prevOffset = 0;
		if (blockIndex > 0)
		{
			prevOffset = mFileEntry->CoderOffsets()[blockIndex - 1];
		}
		mSourceStream->SetPosition(prevOffset);
#ifdef MEDUSA_SAFE_CHECK
		if (nextOffset<=prevOffset)
		{
			Log::AssertFailedFormat("Invalid coder offsets:{}->{}", prevOffset, nextOffset);
			return 0;
		}
#endif
		size_t size = nextOffset - prevOffset;
		auto data = mSourceStream->ReadData(size);
		
		MemoryStream dataStream(data);
		return mCoderChain->Decode(dataStream, output);
	}

	return 0;
}



MEDUSA_END;
