// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileSystem.h"
#include "Core/System/System.h"
#include "Core/IO/Package/IPackage.h"
#include "Core/IO/Package/DirectoryPackage.h"
#include "Core/IO/Package/MemoryPackage.h"
#include "Core/IO/Package/Binary/BinaryPackage.h"
#include "Core/IO/Package/ZipPackage.h"
#include "Core/IO/FileInfo.h"
#include "Core/IO/Package/PackageFactory.h"
#include "Core/IO/FileId.h"
#include "Core/IO/Map/FileMapTagItem.h"
#include "Core/IO/Map/FileMapOrderItem.h"


MEDUSA_BEGIN;

FileSystem::FileSystem()
{
	mCurrentTag = PublishTarget::MatchAll;

	//read only memory package
	mMemoryPackage = new MemoryPackage("__Medusa__MemoryPackage", PackagePriority::Memory, 1);
	mMemoryPackage->Initialize();
	mMemoryPackage->SetParent(this);
	mPackages.Add(mMemoryPackage);
}

FileSystem::~FileSystem()
{
	Uninitialize();
}

bool FileSystem::Uninitialize()
{
	SAFE_DELETE_DICTIONARY_VALUE(mTagItems);
	SAFE_DELETE_COLLECTION(mPackages);

	mMemoryPackage = nullptr;
	mPackages.Clear();
	mCurrentTag = PublishTarget::MatchAll;
	mSortedTagItems.Clear();
	mValidTagList.Clear();
	return true;
}

bool FileSystem::Initialize(CoderList coder/*=0*/, const MemoryByteData& key /*= MemoryByteData::Empty*/)
{
	return Initialize(coder, coder,key);
}

bool FileSystem::Initialize(CoderList readonlyPathCoder, CoderList writablePathCoder, const MemoryByteData& key /*= MemoryByteData::Empty*/)
{
	//read only path
	StringRef readonlyPath = System::Instance().ReadonlyPath();

	IPackage* readonlyDirectoryPackage = new DirectoryPackage(readonlyPath, PackagePriority::App, 0, true);
	readonlyDirectoryPackage->SetKey(key);
	readonlyDirectoryPackage->SetFlags(PackageFlags::Readonly);
	readonlyDirectoryPackage->SetCoders(readonlyPathCoder);
	readonlyDirectoryPackage->Initialize();
	mPackages.Add(readonlyDirectoryPackage);

	//read only package
	List<HeapString> outFiles;
	Directory::GetFiles(readonlyPath, outFiles, true);
	for (HeapString& file : outFiles)
	{
		FileType fileType = FileInfo::ExtractType(file);
		if (PackageFactory::IsPackage(fileType))
		{
			IPackage* package = PackageFactory::Create(fileType, file, PackagePriority::App, 0);
			package->SetKey(key);
			package->Initialize();
			mPackages.Add(package); 
		}
	}

	//writable path
	StringRef writablePath = System::Instance().WritablePath();
	IPackage* writableDirectoryPackage = new DirectoryPackage(writablePath, PackagePriority::Downloaded, 0, true);
	writableDirectoryPackage->SetFlags(PackageFlags::None);
	writableDirectoryPackage->SetCoders(writablePathCoder);
	writableDirectoryPackage->SetKey(key);
	writableDirectoryPackage->Initialize();
	mPackages.Add(writableDirectoryPackage);
	//writable package

	outFiles.Clear();
	Directory::GetFiles(writablePath, outFiles, true);
	for (HeapString& file : outFiles)
	{
		FileType fileType = FileInfo::ExtractType(file);
		if (PackageFactory::IsPackage(fileType))
		{
			IPackage* package = PackageFactory::Create(fileType, file, PackagePriority::Downloaded, 0);
			package->SetKey(key);
			package->Initialize();
			mPackages.Add(package);
		}
	}

	ReloadTagItems();
	ApplyTagHelper(PublishTarget::MatchAll);

	return true;
}

#pragma region Package

const IPackage* FileSystem::FindPackage(const StringRef& name) const
{
	for (const auto* item : mPackages)
	{
		if (item->Path() == name)
		{
			return item;
		}
	}
	return nullptr;
}

IPackage* FileSystem::FindPackageMutable(const StringRef& name)
{
	for (auto* item : mPackages)
	{
		if (item->Path() == name)
		{
			return item;
		}
	}
	return nullptr;
}

void FileSystem::AddPackage(IPackage* package)
{
	mPackages.Add(package);
	package->SetParent(this);

	if (package->RootDir().HasFileRecursively())
	{
		ReloadTagItems();
	}
}

IPackage* FileSystem::RemovePackage(StringRef name)
{
	uintp count = mPackages.Count();
	FOR_EACH_SIZE(i, count)
	{
		auto* item = mPackages[i];
		if (item->Path() == name)
		{
			mPackages.RemoveAt(i);
			item->SetParent(nullptr);
			ReloadTagItems();
			return item;
		}
	}
	return nullptr;
}

void FileSystem::ApplyTag(const PublishTarget& tag)
{
	RETURN_IF_EQUAL(mCurrentTag, tag);
	ApplyTagHelper(tag);
}

void FileSystem::ApplyTagHelper(const PublishTarget& tag)
{
	mCurrentTag = tag;
	mValidTagList.Clear();
	FOR_EACH_COLLECTION_STL(i, mSortedTagItems.STLItems())
	{
		FileMapTagItem* tagItem = i->second;
		int diffScore = tagItem->UpdateDiffScore(tag);
		if (diffScore != Math::IntMinValue)
		{
			mValidTagList.Add(tagItem);
		}
	}
}


#pragma endregion Package


const FileEntry* FileSystem::FindFile(const FileIdRef& fileId) const
{
	for (const auto* tagItem : mValidTagList)
	{
		const FileMapOrderItem* orderItem = tagItem->FindOrderItem(fileId);
		if (orderItem != nullptr)
		{
			return orderItem->GetFileEntry();
		}
	}
	return nullptr;
}

FileEntry* FileSystem::FindFile(const FileIdRef& fileId)
{
	for (auto* tagItem : mValidTagList)
	{
		FileMapOrderItem* orderItem = tagItem->FindOrderItem(fileId);
		if (orderItem != nullptr)
		{
			return orderItem->MutableFileEntry();
		}
	}
	return nullptr;
}

const IStream* FileSystem::ReadFile(const FileIdRef& fileId, FileDataType dataType /*= FileDataType::Binary*/) const
{
	auto fileEntry = FindFile(fileId);
	RETURN_NULL_IF_NULL(fileEntry);
	return fileEntry->Read(dataType);
}

MemoryByteData FileSystem::ReadAllData(const FileIdRef& fileId, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	auto fileEntry = FindFile(fileId);
	if (fileEntry != nullptr)
	{
		return ReadAllData(*fileEntry, mode);
	}

	return MemoryByteData::Empty;
}


MemoryByteData FileSystem::ReadAllData(const FileEntry& fileEntry, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	return fileEntry.ReadAllData(mode);
}

MemoryByteData FileSystem::ReadAllData(const FileMapOrderItem& orderItem, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	return orderItem.GetFileEntry()->ReadAllData(mode);
}


#pragma region Map


const FileMapNameItem* FileSystem::FindNameItem(StringRef name) const
{
	for (const auto* tagItem : mValidTagList)
	{
		const FileMapNameItem* nameItem = tagItem->Find(name);
		if (nameItem != nullptr)
		{
			return nameItem;
		}
	}
	return nullptr;
}

FileMapNameItem* FileSystem::FindNameItem(StringRef name)
{
	for (auto* tagItem : mValidTagList)
	{
		FileMapNameItem* nameItem = tagItem->Find(name);
		if (nameItem != nullptr)
		{
			return nameItem;
		}
	}
	return nullptr;
}

const FileMapOrderItem* FileSystem::FindOrderItem(const FileIdRef& fileId) const
{
	for (const auto* tagItem : mValidTagList)
	{
		const FileMapNameItem* nameItem = tagItem->Find(fileId.Name);
		CONTINUE_IF_NULL(nameItem);
		const FileMapOrderItem* orderItem = nameItem->Find((uint)fileId.Order);
		if (orderItem != nullptr)
		{
			return orderItem;
		}
	}
	return nullptr;
}

FileMapOrderItem* FileSystem::FindOrderItem(const FileIdRef& fileId)
{
	for (auto* tagItem : mValidTagList)
	{
		FileMapOrderItem* orderItem = tagItem->FindOrderItem(fileId);

		if (orderItem != nullptr)
		{
			return orderItem;
		}
	}
	return nullptr;
}

bool FileSystem::ContainsOrderItem(const FileIdRef& fileId) const
{
	return FindOrderItem(fileId) != nullptr;
}

const FileMapTagItem* FileSystem::FindTagItem(const PublishTarget& tag) const
{
	return mTagItems.TryGetValueWithFailed(tag.Tag(), nullptr);
}

FileMapTagItem* FileSystem::FindTagItem(const PublishTarget& tag)
{
	return mTagItems.TryGetValueWithFailed(tag.Tag(), nullptr);
}

FileMapTagItem* FileSystem::FindOrCreateTagItem(const PublishTarget& tag)
{
	FileMapTagItem* item = mTagItems.TryGetValueWithFailed(tag.Tag(), nullptr);
	if (item == nullptr)
	{
		item = new FileMapTagItem(tag);
		mTagItems.Add(tag.Tag(), item);
		mSortedTagItems.Add(tag, item);
	}

	return item;
}

bool FileSystem::TryGetOrderItems(StringRef name, List<const FileMapOrderItem*>& outOrderItems) const
{
	for (const auto* tagItem : mValidTagList)
	{
		const FileMapNameItem* nameItem = tagItem->Find(name);
		if (nameItem != nullptr)
		{
			for (auto& orderItem : nameItem->Items())
			{
				outOrderItems.Add(orderItem.Value);
			}
			return true;
		}
	}
	return false;
}

bool FileSystem::TryGetOrderItems(StringRef name, List<FileMapOrderItem*>& outOrderItems)
{
	for (auto* tagItem : mValidTagList)
	{
		FileMapNameItem* nameItem = tagItem->Find(name);
		if (nameItem != nullptr)
		{
			for (auto& orderItem : nameItem->MutableItems())
			{
				outOrderItems.Add(orderItem.Value);
			}
			return true;
		}
	}
	return false;
}

void FileSystem::ReloadTagItems()
{
	SAFE_DELETE_DICTIONARY_VALUE(mTagItems);
	mSortedTagItems.Clear();

	List<FileEntry*> outFiles;
	for (const IPackage* package : mPackages)
	{
		const auto& rootDir = package->RootDir();
		outFiles.Clear();
		rootDir.GetFiles(outFiles);
		for (auto* file : outFiles)
		{
			MapFile(*file, false);
		}
	}

	ApplyTagHelper(mCurrentTag);
}



FileMapOrderItem* FileSystem::MapFile(FileEntry& fileEntry, bool tryReload/*=false*/)
{
	FileId fileId = FileId::ParseFrom(fileEntry.Name());
	PublishTarget tag = PublishTarget::Parse(fileEntry.Name());
	bool isTagChanged = false;
	auto* tagItem = FindTagItem(tag);
	if (tagItem == nullptr)
	{
		tagItem = new FileMapTagItem(tag);
		mTagItems.Add(tag.Tag(), tagItem);
		mSortedTagItems.Add(tag, tagItem);
		isTagChanged = true;
	}

	auto orderItem = tagItem->FindOrCreateOrderItem(fileId);
	orderItem->AddFileEntry(fileEntry);

	if (tryReload&&isTagChanged)
	{
		ApplyTagHelper(mCurrentTag);
	}
	return orderItem;
}

bool FileSystem::UnmapFile(const FileEntry& fileEntry, bool tryReload/*=false*/)
{
	//remove file is rarely used, so we search all items to find

	List<FileMapTagItem*> resultItems;
	for (auto& tagItemPair : mTagItems)
	{
		auto* tagItem = tagItemPair.Value;
		if (tagItem->RemoveOrderItems(fileEntry))
		{
			resultItems.Add(tagItem);
		}
	}

	if (!resultItems.IsEmpty())
	{
		bool isTagChanged = false;
		for (auto* item : resultItems)
		{
			if (item->IsEmpty())
			{
				mTagItems.RemoveKey(item->Tag().Tag());
				delete item;
				isTagChanged = true;
			}
		}

		resultItems.Clear();
		if (isTagChanged&&tryReload)
		{
			ApplyTagHelper(mCurrentTag);
		}
		return true;
	}
	return false;
}

#pragma endregion Map


MEDUSA_END;

