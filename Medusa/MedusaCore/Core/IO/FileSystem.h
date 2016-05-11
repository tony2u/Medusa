// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/IO/FileIdRef.h"
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Log/Log.h"
#include "Core/Collection/List.h"
#include "Core/Coder/CoderDefines.h"
#include "Core/Collection/SortedList.h"
#include "Core/Collection/SortedDictionary.h"
#include "Core/IO/Package/IPackage.h"
#include "Core/IO/Package/MemoryPackage.h"
#include "Core/Module/IModule.h"

MEDUSA_BEGIN;

class FileSystem :public Singleton<FileSystem>,public IModule
{
	friend class IPackage;
	friend class Singleton < FileSystem >;
	FileSystem();
	~FileSystem();
public:
	uint64 Coders()const { return mCoders; }
	void SetCoders(uint64 val) { mCoders = val; }

	MemoryData CoderKey()const { return mCoderKey; }
	void SetCoderKey(MemoryData val) { mCoderKey = val; }

	bool Initialize(CoderList readonlyPathCoder, CoderList writablePathCoder, const MemoryData& key = MemoryData::Empty);
	bool Initialize(CoderList coder , const MemoryData& key);

	virtual bool Initialize();
	virtual bool Uninitialize();
protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnUnload(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnReload(IEventArg& e = IEventArg::Empty) override;


public:
#pragma region Package
	MemoryPackage& Memory() { return *mMemoryPackage; }
	DirectoryPackage& ReadDir() { return *mReadDirPackage; }
	DirectoryPackage& WriteDir() { return *mWriteDirPackage; }

	const IPackage* FindPackage(const StringRef& name)const;
	IPackage* FindPackageMutable(const StringRef& name);

	void AddPackage(IPackage* package);
	IPackage* RemovePackage(StringRef name);
	void ApplyTag(const PublishTarget& tag);

	DirectoryPackage* AddDirectory(const StringRef& path, PackageFlags flags = PackageFlags::Readonly, PackagePriority priority = PackagePriority::App, CoderList coder = 0, const MemoryData& key = MemoryData::Empty, bool reloadTagItems = true);
#pragma endregion Package

	const FileEntry* Find(const FileIdRef& fileId)const;
	FileEntry* Find(const FileIdRef& fileId);
	bool Exists(const FileIdRef& fileId)const { return Find(fileId) != nullptr; }
	bool AssertExists(const FileIdRef& fileId)const;
	FileIdRef ExistsOr(const FileIdRef& fileId, const FileIdRef& optional)const;
	StringRef ExistsOr(const StringRef& fileId, const StringRef& optional)const;

public:
	const IStream* Read(const FileIdRef& fileId, FileDataType dataType = FileDataType::Binary)const;

	MemoryData ReadAllData(const FileIdRef& fileId, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	MemoryData ReadAllData(const FileEntry& fileEntry, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	MemoryData ReadAllData(const FileMapOrderItem& orderItem, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;

	HeapString ReadAllText(const FileIdRef& fileId)const;
	HeapString ReadAllText(const FileEntry& fileEntry)const;
	HeapString ReadAllText(const FileMapOrderItem& orderItem)const;

	HeapString GetRealPath(const FileIdRef& fileId)const;

#pragma region Map
public:
	const FileMapTagItem* FindTagItem(const PublishTarget& tag)const;
	FileMapTagItem* FindTagItem(const PublishTarget& tag);
	FileMapTagItem* FindOrCreateTagItem(const PublishTarget& tag);

	const FileMapNameItem* FindNameItem(StringRef name)const;
	FileMapNameItem* FindNameItem(StringRef name);

	const FileMapOrderItem* FindOrderItem(const FileIdRef& fileId)const;
	FileMapOrderItem* FindOrderItem(const FileIdRef& fileId);
	bool ContainsOrderItem(const FileIdRef& fileId)const;

	bool TryGetOrderItems(StringRef name, List<const FileMapOrderItem*>& outOrderItems)const;
	bool TryGetOrderItems(StringRef name, List<FileMapOrderItem*>& outOrderItems);

	bool TryGetOrderItemsWithExtension(StringRef ext, List<const FileMapOrderItem*>& outOrderItems)const;
	bool TryGetOrderItemsWithExtension(StringRef ext, List<FileMapOrderItem*>& outOrderItems);

	bool TryGetNameItemsWithExtension(StringRef ext, List<const FileMapNameItem*>& outItems)const;
	bool TryGetNameItemsWithExtension(StringRef ext, List<FileMapNameItem*>& outItems);

	FileMapOrderItem* MapFileReference(const StringRef& fileName, FileEntry& targetFileEntry, void* region = nullptr, bool tryReload = false);

protected:
	void ReloadTagItems();
	FileMapOrderItem* MapFile(FileEntry& fileEntry, bool tryReload = false);
	bool UnmapFile(const FileEntry& fileEntry, bool tryReload = false);

	void ApplyTagHelper(const PublishTarget& tag);

#pragma endregion Map
protected:
	SortedList<IPackage*, EqualCompare<IPackage*>, CustomCompareForPointer<IPackage*>> mPackages;
	MemoryPackage* mMemoryPackage = nullptr;		//weak
	DirectoryPackage* mReadDirPackage = nullptr;	//weak
	DirectoryPackage* mWriteDirPackage = nullptr;	//weak
protected:
	PublishTarget mCurrentTag;

	Dictionary<PublishTarget, FileMapTagItem*> mTagItems;
	SortedDictionary<PublishTarget, FileMapTagItem*> mSortedTagItems;
	List<FileMapTagItem*> mValidTagList;

	uint64 mCoders = 0;
	MemoryData mCoderKey;
};


MEDUSA_END;