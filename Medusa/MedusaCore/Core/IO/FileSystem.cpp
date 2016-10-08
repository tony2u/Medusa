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
#include "Core/IO/File.h"


MEDUSA_BEGIN;

FileSystem::FileSystem()
	:IModule("FileSystem")
{
	this->Retain();		//retain self
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
	mReadDirPackage = nullptr;
	mWriteDirPackage = nullptr;

	mPackages.Clear();
	mCurrentTag = PublishTarget::MatchAll;
	mSortedTagItems.Clear();
	mValidTagList.Clear();
	return true;
}

bool FileSystem::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	return Initialize(mCoders, mCoderKey);
}

bool FileSystem::OnUnload(IEventArg& e /*= IEventArg::Empty*/)
{
	Uninitialize();
	return true;
}

bool FileSystem::OnReload(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}

bool FileSystem::Initialize()
{
	return Initialize(mCoders, mCoderKey);
}

bool FileSystem::Initialize(CoderList coder, const MemoryData& key)
{
	return Initialize(coder, coder, key);
}


bool FileSystem::Initialize(CoderList readonlyPathCoder, CoderList writablePathCoder, const MemoryData& key /*= MemoryByteData::Empty*/)
{
	//read only path
	StringRef readonlyPath = System::Instance().ReadonlyPath();
	mReadDirPackage = AddDirectory(readonlyPath, PackageFlags::Readonly, PackagePriority::App, readonlyPathCoder, key, false);

	//writable path
	StringRef writablePath = System::Instance().WritablePath();
	mWriteDirPackage = AddDirectory(writablePath, PackageFlags::None, PackagePriority::Downloaded, writablePathCoder, key, false);

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


DirectoryPackage* FileSystem::AddDirectory(const StringRef& path,
	PackageFlags flags /*= PackageFlags::Readonly*/,
	PackagePriority priority /*= PackagePriority::App*/,
	CoderList coder/*=0*/,
	const MemoryData& key /*= MemoryByteData::Empty*/,
	bool reloadTagItems /*= true*/)
{
	DirectoryPackage* package = new DirectoryPackage(path, priority, 0, true);
	package->SetKey(key);
	package->SetFlags(flags);
	package->SetCoders(coder);
	package->Initialize();
	mPackages.Add(package);

	List<HeapString> outFiles;
	Directory::GetFiles(path, outFiles, true);
	for (HeapString& file : outFiles)
	{
		FileType fileType = FileInfo::ExtractType(file);
		if (PackageFactory::IsPackage(fileType))
		{
			IPackage* childPackage = PackageFactory::Create(fileType, file, priority, 0);
			childPackage->SetKey(key);
			if (childPackage->Initialize())
			{
				mPackages.Add(childPackage);
			}
			else
			{
				SAFE_DELETE(childPackage);
			}
		}
	}

	if (reloadTagItems)
	{
		ReloadTagItems();
	}
	return package;
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
	for (const auto& i : mSortedTagItems.STLItems())
	{
		FileMapTagItem* tagItem = i.second;
		int diffScore = tagItem->UpdateDiffScore(tag);
		if (diffScore != Math::IntMinValue)
		{
			mValidTagList.Add(tagItem);
		}
	}
}


#pragma endregion Package


const FileEntry* FileSystem::Find(const FileIdRef& fileId) const
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

FileEntry* FileSystem::Find(const FileIdRef& fileId)
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

bool FileSystem::Exists(const FileIdRef& fileId) const
{
	if (fileId.IsPath())
	{
		std::unique_ptr<FileStream> steam(new FileStream());
		HeapString path = System::Instance().GetWritablePath(fileId.Name);
		RETURN_TRUE_IF(File::Exists(path));

		path = System::Instance().GetReadonlyPath(fileId.Name);
		return File::Exists(path);
	}
	return Find(fileId) != nullptr;
}

bool FileSystem::AssertExists(const FileIdRef& fileId) const
{
	if (Exists(fileId))
	{
		return true;
	}

	Log::AssertFailedFormat("Cannot find {}", fileId);
	return false;
}

FileIdRef FileSystem::ExistsOr(const FileIdRef& fileId, const FileIdRef& optional) const
{
	return Exists(fileId) ? fileId : optional;
}

StringRef FileSystem::ExistsOr(const StringRef& fileId, const StringRef& optional) const
{
	return Exists(fileId) ? fileId : optional;
}


Share<const IStream> FileSystem::Read(const FileIdRef& fileId, FileDataType dataType /*= FileDataType::Binary*/) const
{
	if (fileId.IsPath())
	{
		std::unique_ptr<FileStream> steam(new FileStream());
		HeapString path = System::Instance().GetWritablePath(fileId.Name);
		if (steam->Open(path, FileOpenMode::ReadOnly, dataType))
		{
			return steam.release();
		}

		path = System::Instance().GetReadonlyPath(fileId.Name);
		if (steam->Open(path, FileOpenMode::ReadOnly, dataType))
		{
			return steam.release();
		}


		return nullptr;
	}

	auto fileEntry = Find(fileId);
	RETURN_NULL_IF_NULL(fileEntry);
	return fileEntry->Read(dataType);
}

MemoryData FileSystem::ReadAllData(const FileIdRef& fileId, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	if (fileId.IsPath())
	{
		HeapString path = System::Instance().GetWritablePath(fileId.Name);
		MemoryData data = File::ReadAllData(path);
		if (data.IsValid())
		{
			return data;
		}

		path = System::Instance().GetReadonlyPath(fileId.Name);
		return File::ReadAllData(path);
	}

	auto fileEntry = Find(fileId);
	if (fileEntry != nullptr)
	{
		return ReadAllData(*fileEntry, mode);
	}

	return MemoryData::Empty;
}


MemoryData FileSystem::ReadAllData(const FileEntry& fileEntry, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	return fileEntry.ReadAllData(mode);
}

MemoryData FileSystem::ReadAllData(const FileMapOrderItem& orderItem, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	return orderItem.GetFileEntry()->ReadAllData(mode);
}


HeapString FileSystem::ReadAllText(const FileIdRef& fileId) const
{
	if (fileId.IsPath())
	{
		HeapString path = System::Instance().GetWritablePath(fileId.Name);
		HeapString str = File::ReadAllText(path);
		if (!str.IsEmpty())
		{
			return str;
		}

		path = System::Instance().GetReadonlyPath(fileId.Name);
		return File::ReadAllText(path);
	}


	auto data = ReadAllData(fileId);
	HeapString str= HeapString::Take(data);
	data.ForceSetDataAndSize(nullptr, 0);
	return str;
}


HeapString FileSystem::ReadAllText(const FileEntry& fileEntry) const
{
	auto data = ReadAllData(fileEntry);
	HeapString str = HeapString::Take(data);
	data.ForceSetDataAndSize(nullptr, 0);
	return str;
}

HeapString FileSystem::ReadAllText(const FileMapOrderItem& orderItem) const
{
	auto data = ReadAllData(orderItem);
	HeapString str = HeapString::Take(data);
	data.ForceSetDataAndSize(nullptr, 0);
	return str;
}


HeapString FileSystem::GetRealPath(const FileIdRef& fileId) const
{
	if (fileId.IsPath())
	{
		HeapString path = System::Instance().GetWritablePath(fileId.Name);
		if (File::Exists(path))
		{
			return path;
		}

		path = System::Instance().GetReadonlyPath(fileId.Name);
		if (File::Exists(path))
		{
			return path;
		}

		return HeapString::Empty;
	}

	auto fileEntry = Find(fileId);
	if (fileEntry != nullptr&&fileEntry->FirstBlockId() == Math::UIntMaxValue&&fileEntry->Storage()->Coders() == 0)
	{
		return fileEntry->Path();
	}

	return HeapString::Empty;
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
	return mTagItems.GetOptional(tag.Tag(), nullptr);
}

FileMapTagItem* FileSystem::FindTagItem(const PublishTarget& tag)
{
	return mTagItems.GetOptional(tag.Tag(), nullptr);
}

FileMapTagItem* FileSystem::FindOrCreateTagItem(const PublishTarget& tag)
{
	FileMapTagItem* item = mTagItems.GetOptional(tag.Tag(), nullptr);
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


bool FileSystem::TryGetOrderItemsWithExtension(StringRef ext, List<const FileMapOrderItem*>& outOrderItems) const
{
	for (const auto* tagItem : mValidTagList)
	{
		for (const auto& nameItemPair : tagItem->Items())
		{
			const FileMapNameItem* nameItem = nameItemPair.Value;
			if (nameItem->Name().EndWith(ext))
			{
				for (auto& orderItem : nameItem->Items())
				{
					outOrderItems.Add(orderItem.Value);
				}
			}
		}
	}
	return true;
}

bool FileSystem::TryGetOrderItemsWithExtension(StringRef ext, List<FileMapOrderItem*>& outOrderItems)
{
	for (const auto* tagItem : mValidTagList)
	{
		for (auto& nameItemPair : tagItem->Items())
		{
			FileMapNameItem* nameItem = nameItemPair.Value;
			if (nameItem->Name().EndWith(ext))
			{
				for (auto& orderItem : nameItem->Items())
				{
					outOrderItems.Add(orderItem.Value);
				}
			}
		}
	}
	return true;
}

bool FileSystem::TryGetNameItemsWithExtension(StringRef ext, List<const FileMapNameItem*>& outItems)const
{
	for (const auto* tagItem : mValidTagList)
	{
		for (const auto& nameItemPair : tagItem->Items())
		{
			const FileMapNameItem* nameItem = nameItemPair.Value;
			if (nameItem->Name().EndWith(ext))
			{
				outItems.Add(nameItem);
			}
		}
	}
	return true;
}

bool FileSystem::TryGetNameItemsWithExtension(StringRef ext, List<FileMapNameItem*>& outItems)
{
	for (const auto* tagItem : mValidTagList)
	{
		for (auto& nameItemPair : tagItem->Items())
		{
			FileMapNameItem* nameItem = nameItemPair.Value;
			if (nameItem->Name().EndWith(ext))
			{
				outItems.Add(nameItem);
			}
		}
	}
	return true;
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


FileMapOrderItem* FileSystem::MapFileReference(const StringRef& fileName, FileEntry& targetFileEntry, void* region /*= nullptr*/, bool tryReload /*= false*/)
{
	FileId fileId = FileId::ParseFrom(fileName);
	PublishTarget tag = PublishTarget::Parse(fileName);
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
	orderItem->AddFileEntry(targetFileEntry, fileName, region);

	if (tryReload&&isTagChanged)
	{
		ApplyTagHelper(mCurrentTag);
	}
	return orderItem;
}

void FileSystem::UnmapFileReference(FileMapOrderItem* orderItem, FileEntry& targetFileEntry)
{
	orderItem->RemoveFileEntry(targetFileEntry);
	if (!orderItem->IsValid())
	{
		//remove this file order
		auto nameItem= orderItem->Parent();
		nameItem->Remove(orderItem->Order());
		delete orderItem;

		if (nameItem->IsEmpty())
		{
			auto tagItem = nameItem->Parent();
			tagItem->Remove(nameItem->Name());
			delete nameItem;

			if (tagItem->IsEmpty())
			{
				mTagItems.RemoveKey(tagItem->Tag());
				mSortedTagItems.RemoveKey(tagItem->Tag());
				mValidTagList.Remove(tagItem);
				delete tagItem;
			}
		}

	}
}

FileMapOrderItem* FileSystem::MapFile(FileEntry& fileEntry, bool tryReload/*=false*/)
{
	return MapFileReference(fileEntry.Name(), fileEntry, nullptr, tryReload);
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

