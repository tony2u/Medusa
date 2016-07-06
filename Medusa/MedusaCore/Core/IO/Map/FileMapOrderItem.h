// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/SortedDictionary.h"
#include "Core/IO/Package/IPackage.h"
#include "Core/Pattern/TuplePattern.h"

MEDUSA_BEGIN;

struct FileEntryRef
{
	FileEntry* Entry = nullptr;
	HeapString RegionName;
	void* Region = nullptr;	//qucik access
	FileEntryRef() = default;
	FileEntryRef(FileEntry* p1, const StringRef& p2, void* p3) :Entry(p1), RegionName(p2), Region(p3) {}
	bool operator==(const FileEntryRef& val)const { return Entry == val.Entry&&Region == val.Region&&RegionName == val.RegionName; }
	bool operator!=(const FileEntryRef& val)const { return Entry != val.Entry || Region != val.Region || RegionName != val.RegionName; }
	bool operator<(const FileEntryRef& val)const { return Entry < val.Entry&&Region < val.Region&&RegionName < val.RegionName; }
	intp HashCode()const { return HashUtility::Hash(Entry) ^ HashUtility::Hash(Region) ^ HashUtility::Hash(RegionName); }
};


class FileMapOrderItem
{
public:
	~FileMapOrderItem();
	FileMapOrderItem(uint order = 0);

	bool operator<(const FileMapOrderItem& other)const { return mOrder < other.mOrder; }
	bool operator==(const FileMapOrderItem& other)const { return mOrder == other.mOrder; }
public:
	FileIdRef GetFileId()const;
	uint Order() const { return mOrder; }
	void SetOrder(uint val) { mOrder = val; }
	int DiffScore() const;
	FileMapNameItem* Parent() const { return mParent; }
	void SetParent(FileMapNameItem* val) { mParent = val; }

	const FileEntry* GetFileEntry() const { return mFirstValidFileEntry!=nullptr?mFirstValidFileEntry->Entry:nullptr; }
	FileEntry* MutableFileEntry() { return mFirstValidFileEntry!=nullptr?mFirstValidFileEntry->Entry:nullptr; }

	void AddFileEntry(FileEntry& fileEntry, const StringRef& name = StringRef::Empty, void* region = nullptr);
	bool RemoveFileEntry(const FileEntry& fileEntry);
	bool RemoveFileEntryRegion(const FileEntry& fileEntry);


	void* Region() const { return mFirstValidFileEntry!=nullptr?mFirstValidFileEntry->Region:nullptr; }
	StringRef RegionName() const
	{
		if (mFirstValidFileEntry != nullptr)
		{
			return mFirstValidFileEntry->RegionName;
		}
		return StringRef::Empty;
	}

	bool IsValid()const { return !mFiles.IsEmpty(); }
	intp HashCode()const { return mOrder; }
private:
	void UpdateFirstValidFileEntry();
protected:
	uint mOrder = 0;
	FileMapNameItem* mParent = nullptr;

	SortedDictionary<const IPackage*, FileEntryRef, CustomCompareForPointer> mFiles;

	FileEntryRef* mFirstValidFileEntry = nullptr;

};



MEDUSA_END;