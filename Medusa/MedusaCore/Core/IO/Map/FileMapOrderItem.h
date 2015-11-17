// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/SortedDictionary.h"
#include "Core/IO/Package/IPackage.h"

MEDUSA_BEGIN;

class FileMapOrderItem
{
public:
	~FileMapOrderItem();
	FileMapOrderItem(uint order = 0);

	bool operator<(const FileMapOrderItem& other)const { return mOrder < other.mOrder; }
	bool operator==(const FileMapOrderItem& other)const { return mOrder == other.mOrder; }
public:
	uint Order() const { return mOrder; }
	void SetOrder(uint val) { mOrder = val; }
	int DiffScore() const;
	FileMapNameItem* Parent() const { return mParent; }
	void SetParent(FileMapNameItem* val) { mParent = val; }

	const FileEntry* GetFileEntry() const { return mFirstValidFileEntry; }
	FileEntry* MutableFileEntry() { return mFirstValidFileEntry; }



	void AddFileEntry(FileEntry& fileEntry);
	bool RemoveFileEntry(const FileEntry& fileEntry);

	bool IsValid()const { return !mFiles.IsEmpty(); }
	intp HashCode()const { return mOrder; }
private:
	void UpdateFirstValidFileEntry();
protected:
	uint mOrder = 0;
	FileMapNameItem* mParent = nullptr;

	SortedDictionary<const IPackage*, FileEntry*, CustomCompareForPointer<const IPackage*>> mFiles;

	FileEntry* mFirstValidFileEntry = nullptr;

};



MEDUSA_END;