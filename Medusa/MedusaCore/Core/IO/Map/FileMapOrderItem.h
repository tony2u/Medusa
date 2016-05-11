// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/SortedDictionary.h"
#include "Core/IO/Package/IPackage.h"
#include "Core/Pattern/TuplePattern.h"

MEDUSA_BEGIN;

MEDUSA_TUPLE_2(FileEntryRef, FileEntry*, Entry, void*, Region);

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

	const FileEntry* GetFileEntry() const { return mFirstValidFileEntry.Entry; }
	FileEntry* MutableFileEntry() { return mFirstValidFileEntry.Entry; }

	void AddFileEntry(FileEntry& fileEntry,void* region=nullptr);
	bool RemoveFileEntry(const FileEntry& fileEntry);

	void* Region() const { return mFirstValidFileEntry.Region; }

	bool IsValid()const { return !mFiles.IsEmpty(); }
	intp HashCode()const { return mOrder; }
private:
	void UpdateFirstValidFileEntry();
protected:
	uint mOrder = 0;
	FileMapNameItem* mParent = nullptr;

	SortedDictionary<const IPackage*, FileEntryRef, CustomCompareForPointer<const IPackage*>> mFiles;

	FileEntryRef mFirstValidFileEntry;

};



MEDUSA_END;