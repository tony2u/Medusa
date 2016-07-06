// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/BlockCodeWriteStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Storage/FileEntry.h"

MEDUSA_BEGIN;


BlockCodeWriteStream::BlockCodeWriteStream(const Share<IStream>& stream, uint32 blockSize, const CoderChain& coderChain, FileEntry& fileEntry)
	: BlockWriteStream(stream, blockSize),
	mFileEntry(&fileEntry),
	mCoderChain(&coderChain)
{
	mFileEntry->MutableCoderOffsets().Clear();
	mBlockIndex = 0;
	mSourceStream->Rewind();

	mFileEntry->SetSize(0);
	mFileEntry->SetOriginalSize(0);
}


BlockCodeWriteStream::BlockCodeWriteStream(BlockCodeWriteStream&& other)
	:BlockWriteStream(std::move(other)),
	mFileEntry(other.mFileEntry),
	mCoderChain(std::move(other.mCoderChain))
{
	other.mFileEntry = nullptr;
	other.mCoderChain = nullptr;
}



BlockCodeWriteStream& BlockCodeWriteStream::operator=(BlockCodeWriteStream&& other)
{
	if (this != &other)
	{
		Close();
		BlockWriteStream::operator=(std::move(other));
		mCoderChain = other.mCoderChain;
		mFileEntry = other.mFileEntry;

		other.mFileEntry = nullptr;
		other.mCoderChain = nullptr;
	}
	return *this;
}

BlockCodeWriteStream::~BlockCodeWriteStream(void)
{
	Close();
}

uintp BlockCodeWriteStream::Length() const
{
	uintp pos = Position();
	return Math::Max((uintp)mFileEntry->OriginalSize(), pos);
}

size_t BlockCodeWriteStream::WriteBlock(uint blockIndex, const MemoryData& data)
{
	MemoryStream dataStream(data);
	size_t resultSize = mCoderChain->Encode(dataStream, *mSourceStream);
	WriteOffset(resultSize);

	mFileEntry->MutableOriginalSize() += (uint32)data.Size();
	mFileEntry->MutableSize() += (uint32)resultSize;


	return data.Size();
}

void BlockCodeWriteStream::WriteOffset(size_t dataSize)
{
	auto& offsets = mFileEntry->MutableCoderOffsets();
	size_t count = offsets.Count();
	if (count == 0)
	{
		offsets.Add((uint32)dataSize);
	}
	else
	{
		uint32 offset = (uint32)dataSize;
		if (mBlockIndex > 0)
		{
			offset += offsets[mBlockIndex - 1];
		}

		if (mBlockIndex <= count - 1)
		{
			offsets[mBlockIndex] = offset;
		}
		else
		{
			offsets.Add(offset);
		}
	}
}

MEDUSA_END;

