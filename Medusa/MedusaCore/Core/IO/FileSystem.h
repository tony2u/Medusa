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

MEDUSA_BEGIN;

class FileSystem :public Singleton<FileSystem>
{
	friend class IPackage;
	friend class Singleton < FileSystem >;
	FileSystem();
	~FileSystem();
public:
	bool Initialize(CoderList readonlyPathCoder, CoderList writablePathCoder,const MemoryByteData& key=MemoryByteData::Empty);
	bool Initialize(CoderList coder = 0, const MemoryByteData& key = MemoryByteData::Empty);

	bool Uninitialize();
public:
#pragma region Package
	MemoryPackage& Memory() { return *mMemoryPackage; }
	const IPackage* FindPackage(const StringRef& name)const;
	IPackage* FindPackageMutable(const StringRef& name);

	void AddPackage(IPackage* package);
	IPackage* RemovePackage(StringRef name);
	void ApplyTag(const PublishTarget& tag);
#pragma endregion Package

	const FileEntry* FindFile(const FileIdRef& fileId)const;
	FileEntry* FindFile(const FileIdRef& fileId);
	bool ExistsFile(const FileIdRef& fileId)const { return FindFile(fileId) != nullptr; }
public:
	const IStream* ReadFile(const FileIdRef& fileId, FileDataType dataType = FileDataType::Binary)const;

	MemoryByteData ReadAllData(const FileIdRef& fileId, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	MemoryByteData ReadAllData(const FileEntry& fileEntry, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	MemoryByteData ReadAllData(const FileMapOrderItem& orderItem, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
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

protected:
	void ReloadTagItems();
	FileMapOrderItem* MapFile(FileEntry& fileEntry,bool tryReload=false);
	bool UnmapFile(const FileEntry& fileEntry,bool tryReload=false);

	void ApplyTagHelper(const PublishTarget& tag);

#pragma endregion Map
protected:
	SortedList<IPackage*, EqualCompare<IPackage*>, CustomCompareForPointer<IPackage*>> mPackages;
	MemoryPackage* mMemoryPackage;
protected:
	PublishTarget mCurrentTag;
	
	Dictionary<PublishTarget, FileMapTagItem*> mTagItems;
	SortedDictionary<PublishTarget, FileMapTagItem*> mSortedTagItems;
	List<FileMapTagItem*> mValidTagList;
};


MEDUSA_END;