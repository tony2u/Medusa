// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "FileMapOrderItem.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

class FileMapNameItem
{
public:
	FileMapNameItem(StringRef name = StringRef::Empty);
	~FileMapNameItem();
public:
	bool operator<(const FileMapNameItem& other)const { return mName < other.mName; }
	bool operator==(const FileMapNameItem& other) const { return mName == other.mName; }

public:
	StringRef Name() const { return mName; }
	void SetName(const StringRef& name) { mName = name; }

	const FileMapOrderItem* Find(uint order)const;
	FileMapOrderItem* Find(uint order);
	FileMapOrderItem* FindOrCreate(uint order);


	bool Contains(uint order)const;
	FileMapOrderItem* Remove(uint order);

	uint Count()const;

	bool IsEmpty()const { return Count() == 0; }
	FileMapOrderItem* Add(uint order);

	FileMapTagItem* Parent() const { return mParent; }
	void SetParent(FileMapTagItem* val) { mParent = val; }

	bool RemoveOrderItems(const FileEntry& fileEntry);
	const Dictionary<uint, FileMapOrderItem*>& Items() const { return mItems; }
	Dictionary<uint, FileMapOrderItem*>& MutableItems() { return mItems; }


protected:
	HeapString mName;
	Dictionary<uint,FileMapOrderItem*> mItems;
	FileMapOrderItem* mFirstItem=nullptr;
	FileMapTagItem* mParent=nullptr;
};

MEDUSA_END;