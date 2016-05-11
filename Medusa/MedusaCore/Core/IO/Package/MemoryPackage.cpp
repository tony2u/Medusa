// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MemoryPackage.h"
#include "Core/IO/FileIdRef.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;



MemoryPackage::MemoryPackage(const StringRef& path, PackagePriority priority /*= PackagePriority::Downloaded*/, uint version /*= 0*/)
	:IPackage(path, priority, version),
	mBlockSize(FileStorage::DefaultBlockSize)
{

}

MemoryPackage::~MemoryPackage(void)
{

}

bool MemoryPackage::Initialize()
{
	RETURN_FALSE_IF_FALSE(FileStorage::Initialize());
	return true;
}

bool MemoryPackage::Uninitialize()
{
	SAFE_RELEASE_DICTIONARY_VALUE(mMemoryStreamDict);
	return true;
}

bool MemoryPackage::OnCreateDirectory(const StringRef& dir)
{
	return true;
}

bool MemoryPackage::OnRemoveDirectory(DirectoryEntry& dir)
{
	return true;
}

const IStream* MemoryPackage::OnReadFile(const FileEntry& file, FileDataType dataType /*= FileDataType::Binary*/) const
{
	UN_USED(dataType);
	MemoryStream* memoryStream = mMemoryStreamDict.GetOptional(&file, nullptr);
	RETURN_NULL_IF_NULL(memoryStream);

	memoryStream->Rewind();
	SAFE_RETAIN(memoryStream);
	
	return memoryStream;
}

IStream* MemoryPackage::OnWriteFile(FileEntry& file, FileOpenMode openMode /*= FileOpenMode::ReadOnly*/, FileDataType dataType /*= FileDataType::Binary*/)
{
	UN_USED(dataType);
	MemoryStream* memoryStream = mMemoryStreamDict.GetOptional(&file, nullptr);
	if (memoryStream == nullptr)
	{
		if (openMode == FileOpenMode::ReadOnly)
		{
			return nullptr;
		}
		memoryStream = new MemoryStream();
		mMemoryStreamDict.Add(&file, memoryStream);
		SAFE_RETAIN(memoryStream);
	}
	memoryStream->Rewind();
	SAFE_RETAIN(memoryStream);

	return memoryStream;
}

bool MemoryPackage::OnRemoveFile(FileEntry& file)
{
	MemoryStream* stream = mMemoryStreamDict.RemoveKeyOptional(&file, nullptr);
	RETURN_TRUE_IF_NULL(stream);
	return true;
}

FileEntry* MemoryPackage::RegisterMemory(const MemoryData& data, const FileIdRef& fileId)
{
	FileEntry* fileEntry = SaveFile(data, fileId.Name, nullptr, DataReadingMode::DirectMove);
	if (fileEntry != nullptr)
	{
		fileEntry->SetPermission(FilePermission::Read);
	}
	return fileEntry;
}


MEDUSA_END;
