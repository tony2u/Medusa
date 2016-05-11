// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "DirectoryPackage.h"
#include "Core/IO/Directory.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileInfo.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Path.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/IO/File.h"
#include "Core/IO/Package/PackageFactory.h"
#include "Core/IO/FileId.h"


MEDUSA_BEGIN;

Medusa::DirectoryPackage::DirectoryPackage(const StringRef& path, PackagePriority priority /*= PackagePriority::Downloaded*/, uint version /*= 0*/,
	bool isRecursively /*= true*/, const StringRef& searchPattern /*= StringRef::Empty*/)
	:IPackage(path, priority, version),
	mIsRecursively(isRecursively),
	mSearchPattern(searchPattern),
	mBlockSize(FileStorage::DefaultBlockSize)
{
	mRootDir.SetName(mPath);
}

DirectoryPackage::~DirectoryPackage(void)
{

}


bool DirectoryPackage::Initialize()
{
	RETURN_FALSE_IF_FALSE(FileStorage::Initialize());
	List<HeapString> outFiles;

	Directory::GetFiles(mPath, outFiles, mIsRecursively, mSearchPattern);

	for (HeapString& file : outFiles)
	{
		FileType fileType = FileInfo::ExtractType(file);
		CONTINUE_IF(PackageFactory::IsPackage(fileType));
		StringRef subPath = file.ToString().SubString(mPath.Length());
		if (subPath.BeginWith('/')||subPath.BeginWith('\\'))
		{
			subPath = subPath.SubString(1);
		}

		HeapString dir = Path::GetDirectory(subPath);

		DirectoryEntry* dirEntry = FindOrCreateDirectoryEntry(dir);
		if (dirEntry == nullptr)
		{
			Log::AssertFailedFormat("Failed to register dir:{}", dir);
			return false;
		}

		StringRef fileName = Path::GetFileName(subPath);
		FileEntry* fileEntry = FindOrCreateFileEntry(fileName, dirEntry);
		if (fileEntry == nullptr)
		{
			Log::AssertFailedFormat("Failed to register file:{}", file);
			return false;
		}

	}

	return true;
}

bool DirectoryPackage::Uninitialize()
{
	return true;
}

bool DirectoryPackage::OnCreateDirectory(const StringRef& dir)
{
	HeapString absolutePath = Path::Combine(mPath, dir);
	return Directory::CreateDir(absolutePath);
}

bool DirectoryPackage::OnRemoveDirectory(DirectoryEntry& dir)
{
	auto absolutePath = dir.Path();
	return Directory::RemoveDir(absolutePath);
}

const IStream* DirectoryPackage::OnReadFile(const FileEntry& file, FileDataType dataType /*= FileDataType::Binary*/) const
{
	auto absolutePath = file.Path();
	FileStream* fileStream = new FileStream(absolutePath, FileOpenMode::ReadOnly, dataType);
	if (!fileStream->IsOpen())
	{
		Log::FormatError("Cannot open file:{}", absolutePath);
		SAFE_DELETE(fileStream);
	}

	return fileStream;
}

IStream* DirectoryPackage::OnWriteFile(FileEntry& file, FileOpenMode openMode /*= FileOpenMode::ReadOnly*/, FileDataType dataType /*= FileDataType::Binary*/)
{
	auto absolutePath = file.Path();
	FileStream* fileStream = new FileStream(absolutePath, openMode, dataType);
	if (!fileStream->IsOpen())
	{
		Log::FormatError("Cannot open file:{}", absolutePath);
		SAFE_DELETE(fileStream);
	}
	return fileStream;
}

bool DirectoryPackage::OnRemoveFile(FileEntry& file)
{
	auto absolutePath = file.Path();
	return File::Delete(absolutePath);
}

MEDUSA_END;
