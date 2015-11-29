// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BinaryPackage.h"
#include "Core/IO/File.h"
#include "Core/IO/Package/Binary/BinaryBlockReadStream.h"
#include "Core/IO/Package/Binary/BinaryBlockWriteStream.h"
#include "Core/Siren/Siren.h"
#include "Core/Math/Random/Random.h"
#include "Core/Collection/SortedList.h"
#include "Core/Hash/HasherFactory.h"
#include "Core/Coder/CoderChain.h"

MEDUSA_BEGIN;

BinaryPackage::BinaryPackage(const StringRef& path, PackagePriority priority /*= PackagePriority::Downloaded*/, uint version /*= 0*/)
	:IPackage(path, priority, version),
	mRandom(Random::Global())
{
	mHeader.Reset();
}

BinaryPackage::BinaryPackage(Random& random, const StringRef& path, PackagePriority priority /*= PackagePriority::Downloaded*/, uint version /*= 0*/)
	:IPackage(path, priority, version),
	mRandom(random)
{
	mHeader.Reset();
}


BinaryPackage::~BinaryPackage(void)
{
	SAFE_DELETE_COLLECTION(mBlockHeaders);
}


bool BinaryPackage::Initialize()
{
	RETURN_FALSE_IF_FALSE(FileStorage::Initialize());
	if (IsReadOnly())
	{
		RETURN_FALSE_IF_FALSE(mStream.Open(mPath, FileOpenMode::ReadOnly, FileDataType::Binary));
		//mStream.SetBuffer(FileBufferMode::None, nullptr, 0);	//disable buffer as we'll buffer it ourself 
		RETURN_FALSE_IF_FALSE(OnLoaded());
	}
	else
	{
		if (File::Exists(mPath))
		{
			RETURN_FALSE_IF_FALSE(mStream.Open(mPath, FileOpenMode::ReadWrite, FileDataType::Binary));
			RETURN_FALSE_IF_FALSE(OnLoaded());
		}
		else
		{
			RETURN_FALSE_IF_FALSE(mStream.Open(mPath, FileOpenMode::DestoryReadWriteOrCreate, FileDataType::Binary));
		}
	}

	return true;
}

bool BinaryPackage::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mBlockHeaders);
	mStream.Close();

	return true;
}

bool BinaryPackage::Flush()
{
	mStream.Flush();
	return Save();
}

bool BinaryPackage::Save()
{
	uint offset = mHeader.BlockHeadersOffset();
	uintp currentLength = mStream.Length();
	if (offset > currentLength)
	{
		mStream.SetLength(offset);	//expand size
	}

	mStream.Rewind();

	mHeader.SetCoders(mCoderChain.Coders());
	mHeader.WriteTo(mStream);

	SaveBlockHeaders();
	SaveFileStorage();

	uintp pos = mStream.Position();
	currentLength = mStream.Length();
	if (pos < currentLength)
	{
		mStream.SetLength(pos);	//truncate file
	}


	return true;
}

void BinaryPackage::SetKey(const MemoryByteData& val)
{
	FileStorage::SetKey(val);
	mHeader.SetKey(val);
}

bool BinaryPackage::ValidateKey(const MemoryByteData& val) const
{
	return mHeader.ValidateKey(val);
}

bool BinaryPackage::OnLoaded()
{
	//read header
	if (!mHeader.ParseFrom(mStream))
	{
		Log::FormatError("Invalid MPACK header.{}", mPath);
		return false;
	}
	mCoderChain.SetCoders(mHeader.Coders());

	if (!Validate())
	{
		Log::FormatError("Package:{} required key!", mPath);
		return false;
	}


	LoadBlockHeaders();
	LoadFileStorage();

	return true;

}


bool BinaryPackage::LoadBlockHeaders()
{
	uint32 blockCount = mHeader.BlockCount();
	SAFE_DELETE_COLLECTION(mBlockHeaders);
	mBlockHeaders.ForceReserveCount(blockCount);

	uint offset = mHeader.BlockHeadersOffset();
	mStream.SetPosition(offset);

	FOR_EACH_UINT32(i, blockCount)
	{
		mBlockHeaders[i] = new BinaryPackageBlockHeader();
	}

	//read block headers
	FOR_EACH_UINT32(i, blockCount)
	{
		auto& header = mBlockHeaders[i];
		header->Id = i;
		header->NextId = mStream.Read<uint32>();
		if (header->NextId != Math::UIntMaxValue)
		{
			mBlockHeaders[header->NextId]->PrevId = i;
		}
	}

	//read left sizes, because only some block is not full, so store it in individual place would save place
	uint leftBlockCount = mStream.Read<uint32>();
	FOR_EACH_UINT32(i, leftBlockCount)
	{
		uint32 blockId = mStream.Read<uint32>();
		auto* header = mBlockHeaders[blockId];
		header->LeftSize = mStream.Read<uint32>();
	}


	return true;

}

bool BinaryPackage::SaveBlockHeaders()
{
	uint offset = mHeader.BlockHeadersOffset();
	mStream.SetPosition(offset);

	uint32 blockCount = mHeader.BlockCount();

	//write block headers
	uint leftCount = 0;
	FOR_EACH_SIZE(i, blockCount)
	{
		const auto& header = mBlockHeaders[i];
		mStream.Write(header->NextId);
		if (header->LeftSize != 0)
		{
			++leftCount;
		}
	}

	//write left sizes
	mStream.Write(leftCount);

	FOR_EACH_SIZE(i, blockCount)
	{
		const auto& header = mBlockHeaders[i];
		if (header->LeftSize != 0)
		{
			mStream.Write(header->Id);
			mStream.Write(header->LeftSize);
		}
	}


	return true;
}

bool BinaryPackage::LoadFileStorage()
{
	MemoryByteData resultData;
	if (IsEncryptFileNames() && mCoderChain.HasCoders())
	{
		uint dataOriginalSize = mStream.Read<uint32>();
		uint dataSize = mStream.Read<uint32>();
		const auto data = mStream.ReadData(dataSize);

		MemoryStream input(data);
		MemoryStream output(dataOriginalSize, false);
		mCoderChain.Decode(input, output);
		resultData = output.CurrentBuffer();

	}
	else
	{
		uint dataSize = mStream.Read<uint32>();
		resultData = mStream.ReadData(dataSize);
	}

	if (!Siren::DeserializeBinaryTo(resultData, (FileStorage&)*this))
	{
		Log::FormatError("Cannot read file storage data");
		return false;
	}

	return FileStorage::OnLoaded();
}

bool BinaryPackage::SaveFileStorage()
{
	const auto data = Siren::SerializeBinary((FileStorage&)*this);
	if (IsEncryptFileNames() && mCoderChain.HasCoders())
	{
		MemoryStream input(data);
		MemoryStream output;
		uint resultSize = (uint)mCoderChain.Encode(input, output);
		auto outData = output.CurrentBuffer();
		mStream.Write((uint32)data.Size());
		mStream.Write(resultSize);
		mStream.WriteData(outData);
	}
	else
	{
		mStream.Write(data.Size());
		mStream.WriteData(data);
	}

	return true;
}

bool BinaryPackage::Compact()
{
	mStream.Flush();

	uint firstFreeBlockId = mHeader.FirstFreeBlockId();
	RETURN_TRUE_IF_EQUAL(firstFreeBlockId, Math::UIntMaxValue);

	//find all file entry's first block ids
	Dictionary<uint, FileEntry*> firstFileEntries;
	mRootDir.EnumerateFiles([&firstFileEntries](FileEntry* fileEntry) {firstFileEntries.Add(fileEntry->FirstBlockId(), fileEntry); });

	//find all free blocks
	SortedList<BinaryPackageBlockHeader*, EqualCompare<BinaryPackageBlockHeader*>, CustomCompareForPointer<BinaryPackageBlockHeader*>> freeBlocks;
	uint freeBlockId = firstFreeBlockId;
	do
	{
		auto* freeBlockHeader = mBlockHeaders[freeBlockId];
		freeBlocks.Add(freeBlockHeader);
		freeBlockId = freeBlockHeader->NextId;
	} while (freeBlockId != Math::UIntMaxValue);

	//
	uint currentBlockId = mHeader.BlockCount() - 1;
	uint freeCount = (uint32)freeBlocks.Count();
	FOR_EACH_UINT32(i, freeCount)
	{
		auto* freeBlock = freeBlocks[i];
		//find last not free block
		bool isFound = false;
		do
		{
			if (currentBlockId <= i)	//meet the most first free block
			{
				break;
			}

			auto* currentBlock = mBlockHeaders[currentBlockId--];
			if (!currentBlock->IsFree(mHeader.BlockSize()))
			{
				MoveCopyBlock(*currentBlock, *freeBlock, firstFileEntries);
				isFound = true;
				break;
			}
		} while (true);

		BREAK_IF_FALSE(isFound);
	}

	uint resultBlockCount = (uint32)mHeader.BlockCount() - (uint32)freeBlocks.Count();
	mBlockHeaders.ForceSetCount(resultBlockCount);
	mHeader.SetBlockCount(resultBlockCount);
	mHeader.SetFirstFreeBlockId(Math::UIntMaxValue);
	mHeader.SetFreeBlockCount(0);

	return true;
}

float BinaryPackage::SpaceUsage() const
{
	return mHeader.SpaceUsage();
}

float BinaryPackage::CalculateSpaceUsageExactly(uint& outFreeSpace) const
{
	FOR_EACH_SIZE(i, mHeader.BlockCount())
	{
		const auto* block = mBlockHeaders[i];
		if (block->LeftSize != 0)
		{
			outFreeSpace += block->LeftSize;
		}
	}

	uint32 totalSize = mHeader.BlockCount()*mHeader.BlockSize();
	if (totalSize==0)
	{
		return 0.f;
	}
	return 1.f - (float)outFreeSpace / totalSize;

}

BinaryPackageBlockHeader* BinaryPackage::AllocFreeBlock()
{
	uint freeBlockId = mHeader.FirstFreeBlockId();
	if (freeBlockId != Math::UIntMaxValue)
	{
		BinaryPackageBlockHeader* header = mBlockHeaders[freeBlockId];
		if (header->NextId != Math::UIntMaxValue)
		{
			BinaryPackageBlockHeader* nextFreeHeader = mBlockHeaders[header->NextId];
			mHeader.SetFirstFreeBlockId(header->NextId);
			mHeader.SetFreeBlockCount(mHeader.FreeBlockCount() - 1);
			nextFreeHeader->PrevId = Math::UIntMaxValue;
		}
		else
		{
			mHeader.SetFirstFreeBlockId(Math::UIntMaxValue);
			mHeader.SetFreeBlockCount(mHeader.FreeBlockCount() - 1);
		}
		header->NextId = Math::UIntMaxValue;
		return header;
	}

	//alloc a new one
	BinaryPackageBlockHeader* header = new BinaryPackageBlockHeader();
	mBlockHeaders.Add(header);
	mHeader.SetBlockCount((uint32)mBlockHeaders.Count());
	//expand file size
	header->Id = (uint32)mBlockHeaders.Count() - 1;
	header->LeftSize = mHeader.BlockSize();
	uint32 offset = mHeader.GetBlockOffset(header->Id);
	uint32 endOffset = offset + mHeader.BlockSize();
	if (endOffset > mStream.Length())
	{
		mStream.SetLength(endOffset);
	}

	return header;
}

void BinaryPackage::RecycleBlock(BinaryPackageBlockHeader* block)
{
	uint freeBlockId = mHeader.FirstFreeBlockId();

	block->NextId = freeBlockId;
	block->PrevId = Math::UIntMaxValue;
	block->LeftSize = mHeader.BlockSize();

	if (freeBlockId != Math::UIntMaxValue)
	{
		BinaryPackageBlockHeader* header = mBlockHeaders[freeBlockId];
		header->PrevId = block->Id;
	}
	mHeader.SetFirstFreeBlockId(block->Id);
	mHeader.SetFreeBlockCount(mHeader.FreeBlockCount() + 1);
}

void BinaryPackage::RecycleBlockFrom(uint id)
{
	uint count = 0;
	uint freeBlockId = mHeader.FirstFreeBlockId();
	BinaryPackageBlockHeader* prevBlock = nullptr;
	if (freeBlockId != Math::UIntMaxValue)
	{
		prevBlock = mBlockHeaders[freeBlockId];
	}

	while (id != Math::UIntMaxValue)
	{
		auto* block = mBlockHeaders[id];
		id = block->NextId;

		block->NextId = prevBlock != nullptr ? prevBlock->Id : Math::UIntMaxValue;
		block->PrevId = Math::UIntMaxValue;
		block->LeftSize = mHeader.BlockSize();

		if (prevBlock != nullptr)
		{
			prevBlock->PrevId = id;
		}

		prevBlock = block;
		++count;
	}

	mHeader.SetFreeBlockCount(mHeader.FreeBlockCount() + count);
	mHeader.SetFirstFreeBlockId(prevBlock->Id);
}

void BinaryPackage::MoveCopyBlock(BinaryPackageBlockHeader& from, BinaryPackageBlockHeader& to, const Dictionary<uint, FileEntry*>& fileEnties)
{
	uint32 fromOffset = mHeader.GetBlockOffset(from.Id);
	uint32 toOffset = mHeader.GetBlockOffset(to.Id);
	mStream.SetPosition(fromOffset);

	uint fromSize = mHeader.BlockSize() - from.LeftSize;
	auto data = mStream.ReadData(fromSize);

	mStream.SetPosition(toOffset);
	mStream.WriteData(data);

	to.PrevId = from.PrevId;
	to.NextId = from.NextId;
	to.LeftSize = from.LeftSize;

	if (to.PrevId != Math::UIntMaxValue)
	{
		auto* prevBlock = mBlockHeaders[to.PrevId];
		prevBlock->NextId = to.Id;
	}
	if (to.NextId != Math::UIntMaxValue)
	{
		auto* nextBlock = mBlockHeaders[to.NextId];
		nextBlock->PrevId = to.Id;
	}

	FileEntry* fileEntry = fileEnties.TryGetValueWithFailed(from.Id, nullptr);
	if (fileEntry != nullptr)
	{
		fileEntry->SetFirstBlockId(to.Id);
	}

}

const BinaryPackageBlockHeader* BinaryPackage::ReadBlockTo(uint id, MemoryStream& destStream) const
{
	if (id >= mBlockHeaders.Count())
	{
		return nullptr;
	}
	const BinaryPackageBlockHeader* block = mBlockHeaders[id];
	uint32 fromOffset = mHeader.GetBlockOffset(id);
	mStream.SetPosition(fromOffset);
	uint readSize = mHeader.BlockSize() - block->LeftSize;
	destStream.ReserveSize(readSize);
	auto outData = destStream.Buffer();
	outData.ForceSetSize(readSize);
	if (mStream.ReadDataTo(outData) == readSize)
	{
		destStream.SetPosition(readSize);
		return block;
	}
	return nullptr;
}

bool BinaryPackage::WriteBlockTo(uint id, MemoryStream& srcStream)
{
	if (id >= mBlockHeaders.Count())
	{
		return false;
	}
	BinaryPackageBlockHeader* block = mBlockHeaders[id];
	uint32 fromOffset = mHeader.GetBlockOffset(id);
	mStream.SetPosition(fromOffset);
	size_t writeSize = mStream.WriteData(srcStream.CurrentBuffer());
	block->LeftSize = mHeader.BlockSize() - (uint32)writeSize;
	return writeSize == srcStream.Position();
}

BinaryPackageBlockHeader* BinaryPackage::WriteBlock(BinaryPackageBlockHeader* prevBlock, MemoryStream& srcStream)
{
	auto* newBlock = AllocFreeBlock();
	if (!WriteBlockTo(newBlock->Id, srcStream))
	{
		RecycleBlock(newBlock);
		return nullptr;
	}

	if (prevBlock != nullptr)
	{
		prevBlock->NextId = newBlock->Id;
		newBlock->PrevId = prevBlock->Id;
	}
	return newBlock;
}

bool BinaryPackage::OnCopyFile(const FileEntry& from, FileEntry& to)
{
	BinaryPackage* toPackage = (BinaryPackage*)to.Parent()->Storage();
	IPackage* fromPackage = (IPackage*)from.Parent()->Storage();
	CoderList fromCoders = fromPackage->GetFileCoders(from);
	CoderList toCoders = toPackage->GetFileCoders(to);
	if (fromCoders != toCoders || !fromPackage->IsDataCompatiable(*toPackage))
	{
		//copy file with code
		const IStream* readStream = from.Read();
		toPackage->SaveFile(to, *readStream);
		SAFE_RELEASE(readStream);
	}
	else
	{
		if (to.FirstBlockId() != Math::UIntMaxValue)
		{
			//recycle file blocks
			RecycleBlockFrom(to.FirstBlockId());
			to.SetFirstBlockId(Math::UIntMaxValue);
		}

		BinaryPackage* fromPackage2 = (BinaryPackage*)fromPackage;
		uint fromId = from.FirstBlockId();
		MemoryStream tempStream(fromPackage->BlockSize());
		BinaryPackageBlockHeader* toBlock = nullptr;

		bool hasDifferentHasher = fromPackage2->Hasher() != toPackage->Hasher() && toPackage->Hasher() != HasherType::None;
		if (hasDifferentHasher)
		{
			IHasher* hasher = HasherFactory::Instance().Create(toPackage->Hasher());
			while (fromId != Math::UIntMaxValue)
			{
				tempStream.Rewind();
				const auto* fromBlock = fromPackage2->ReadBlockTo(fromId, tempStream);
				hasher->Process(tempStream.CurrentBuffer());
				toBlock = toPackage->WriteBlock(toBlock, tempStream);
				if (to.FirstBlockId() == Math::UIntMaxValue)
				{
					to.SetFirstBlockId(toBlock->Id);
				}
				fromId = fromBlock->NextId;
			}

			hasher->Final();
			to.SetSignature(hasher->ToString());
		}
		else
		{
			while (fromId != Math::UIntMaxValue)
			{
				tempStream.Rewind();
				const auto* fromBlock = fromPackage2->ReadBlockTo(fromId, tempStream);
				toBlock = toPackage->WriteBlock(toBlock, tempStream);
				if (to.FirstBlockId() == Math::UIntMaxValue)
				{
					to.SetFirstBlockId(toBlock->Id);
				}
				fromId = fromBlock->NextId;
			}
			to.SetSignature(from.Signature());

		}

		to.SetOriginalSize(from.OriginalSize());
		to.SetSize(from.Size());
		to.SetCoderOffsets(from.CoderOffsets());
	}

	to.SetPermission(from.Permission());
	return true;
}

bool BinaryPackage::OnCreateDirectory(const StringRef& dir)
{
	return true;
}

bool BinaryPackage::OnRemoveDirectory(DirectoryEntry& dir)
{
	return true;
}

const IStream* BinaryPackage::OnReadFile(const FileEntry& file, FileDataType dataType /*= FileDataType::Binary*/) const
{
	BinaryBlockReadStream* readStream = new BinaryBlockReadStream(mStream, *this, file);
	if (!readStream->IsOpen())
	{
		Log::FormatError("Cannot open file:{}", file.Path());
		SAFE_DELETE(readStream);
	}
	return readStream;
}

IStream* BinaryPackage::OnWriteFile(FileEntry& file, FileOpenMode openMode /*= FileOpenMode::ReadOnly*/, FileDataType dataType /*= FileDataType::Binary*/)
{
	BinaryBlockWriteStream* readStream = new BinaryBlockWriteStream(mStream, *this, file);
	if (!readStream->IsOpen())
	{
		Log::FormatError("Cannot open file:{}", file.Path());
		SAFE_DELETE(readStream);
	}
	return readStream;
}

bool BinaryPackage::OnRemoveFile(FileEntry& file)
{
	//recycle all blocks
	uint blockId = file.FirstBlockId();
	file.SetFirstBlockId(Math::UIntMaxValue);
	RecycleBlockFrom(blockId);

	return true;
}

MEDUSA_END;
