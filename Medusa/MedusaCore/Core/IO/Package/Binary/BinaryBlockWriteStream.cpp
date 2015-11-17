// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BinaryBlockWriteStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Storage/FileEntry.h"
#include "BinaryPackage.h"
#include "BinaryPackageHeader.h"
#include "Core/Math/Random/Random.h"

MEDUSA_BEGIN;


BinaryBlockWriteStream::BinaryBlockWriteStream(IStream& stream, BinaryPackage& package, FileEntry& fileEntry)
	: BlockWriteStream(stream, package.Header().BlockSize()),
	mPackage(&package),
	mFileEntry(&fileEntry)
{
	if (mFileEntry->FirstBlockId() != Math::UIntMaxValue)
	{
		LoadBlockHeaders();
	}
	mFileEntry->SetSize(0);
}


BinaryBlockWriteStream::BinaryBlockWriteStream(BinaryBlockWriteStream&& other)
	:BlockWriteStream(std::move(other)),
	mPackage(other.mPackage),
	mFileEntry(other.mFileEntry),
	mBlockHeaders(std::move(other.mBlockHeaders))
{
	other.mPackage = nullptr;
	other.mFileEntry = nullptr;
}



BinaryBlockWriteStream& BinaryBlockWriteStream::operator=(BinaryBlockWriteStream&& other)
{
	if (this != &other)
	{
		Close();
		mPackage = other.mPackage;
		mFileEntry = other.mFileEntry;
		mBlockHeaders = std::move(other.mBlockHeaders);

		other.mPackage = nullptr;
		other.mFileEntry = nullptr;
	}
	return *this;
}

BinaryBlockWriteStream::~BinaryBlockWriteStream(void)
{
	Close();
	if (!mBlockHeaders.IsEmpty())
	{
		mFileEntry->SetFirstBlockId(mBlockHeaders.First()->Id);
	}
	else
	{
		mFileEntry->SetFirstBlockId(Math::UIntMaxValue);
	}


	mPackage = nullptr;
	mFileEntry = nullptr;
	mBlockHeaders.Clear();
}

bool BinaryBlockWriteStream::Close()
{
	RETURN_FALSE_IF_FALSE(BlockWriteStream::Close());
	if (mBlockIndex + 1 < mBlockHeaders.Count())
	{
		//some block not used
		FOR_EACH_UINT32_BEGIN_END(i, mBlockIndex + 1, mBlockHeaders.Count() - 1)
		{
			auto* block = mBlockHeaders[i];
			mPackage->RecycleBlock(block);
		}
		mBlockHeaders.ForceSetCount(mBlockIndex + 1);
	}
	return true;
}

uintp BinaryBlockWriteStream::Length() const
{
	uintp pos = Position();
	return Math::Max((uintp)mFileEntry->OriginalSize(), pos);
}

size_t BinaryBlockWriteStream::WriteBlock(uint blockIndex, const MemoryByteData& data)
{
	BinaryPackageBlockHeader* blockHeader = nullptr;
	if (blockIndex < mBlockHeaders.Count())
	{
		//in prev 
		blockHeader = mBlockHeaders[blockIndex];
	}
	else
	{
		//new block
		blockHeader = mPackage->AllocFreeBlock();
		if (mBlockHeaders.IsEmpty())
		{
			blockHeader->PrevId = Math::UIntMaxValue;
			mBlockHeaders.Add(blockHeader);
		}
		else
		{
			auto* prevBlockHeader = mBlockHeaders.Last();
			prevBlockHeader->NextId = blockHeader->Id;
			blockHeader->PrevId = prevBlockHeader->Id;
			mBlockHeaders.Add(blockHeader);
		}
	}

	uint32 offset = mPackage->Header().GetBlockOffset(blockHeader->Id);
	mSourceStream->SetPosition(offset);
	size_t resultSize = mSourceStream->WriteData(data);
	

	blockHeader->LeftSize = mPackage->Header().BlockSize() - (uint32)resultSize;
	if (blockHeader->LeftSize != 0)
	{
		//write salt data
		if (mPackage->Header().Flag().IsWriteSaltData())
		{
			MemoryByteData randomData = MemoryByteData::Alloc(blockHeader->LeftSize);
			mPackage->mRandom.NextBytes(randomData);
			mSourceStream->WriteData(randomData);
		}
		blockHeader->NextId = Math::UIntMaxValue;
	}
	return resultSize;
}

void BinaryBlockWriteStream::LoadBlockHeaders()
{
	uint blockId = mFileEntry->FirstBlockId();
	do
	{
		auto* header = mPackage->mBlockHeaders[blockId];
		mBlockHeaders.Add(header);
		blockId = header->NextId;
	} while (blockId != Math::UIntMaxValue);

	mBlockIndex = 0;
}



MEDUSA_END;

