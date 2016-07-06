// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BinaryBlockReadStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/Storage/FileEntry.h"
#include "BinaryPackage.h"
#include "BinaryPackageHeader.h"

MEDUSA_BEGIN;


BinaryBlockReadStream::BinaryBlockReadStream(const Share<IStream>& stream, const BinaryPackage& package, const FileEntry& fileEntry)
	:BlockReadStream(stream, package.Header().BlockSize()),
	mPackage(&package),
	mFileEntry(&fileEntry)
{
	LoadBlockHeaders();
}

BinaryBlockReadStream::BinaryBlockReadStream(BinaryBlockReadStream&& other)
	:BlockReadStream(std::move(other)),
	mPackage(other.mPackage),
	mFileEntry(other.mFileEntry),
	mBlockHeaders(std::move(other.mBlockHeaders))
{
	other.mPackage = nullptr;
	other.mFileEntry = nullptr;
}

BinaryBlockReadStream& BinaryBlockReadStream::operator=(BinaryBlockReadStream&& other)
{
	if (this != &other)
	{
		Close();
		BlockReadStream::operator=(std::move(other));
		mPackage = other.mPackage;
		mFileEntry = other.mFileEntry;
		mBlockHeaders = std::move(other.mBlockHeaders);

		other.mPackage = nullptr;
		other.mFileEntry = nullptr;

	}
	return *this;
}

BinaryBlockReadStream::~BinaryBlockReadStream(void)
{
	Close();
	mPackage = nullptr;
	mFileEntry = nullptr;
	mBlockHeaders.Clear();
}

uintp BinaryBlockReadStream::Length() const
{
	return mFileEntry->Size();
}

size_t BinaryBlockReadStream::LoadBlockTo(uint blockIndex, MemoryStream& output)const
{
	size_t blockCount = mBlockHeaders.Count();
	if (blockIndex < blockCount)
	{
		const auto* header = mBlockHeaders[blockIndex];
		auto offset = mPackage->Header().GetBlockOffset(header->Id);
		mSourceStream->SetPosition(offset);
		uint readSize = mPackage->Header().BlockSize() - header->LeftSize;
		return mSourceStream->ReadToStream(readSize, output);
	}

	return 0;
}

void BinaryBlockReadStream::LoadBlockHeaders()
{
	uint blockId = mFileEntry->FirstBlockId();
	do
	{
		const auto* header = mPackage->mBlockHeaders[blockId];
		mBlockHeaders.Add(header);
		blockId = header->NextId;
	} while (blockId != Math::UIntMaxValue);

	mBlockIndex = Math::UIntMaxValue;
}


MEDUSA_END;
