// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "FileMapNameItem.h"
#include "Core/System/PublishTarget.h"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

class FileMapTagItem
{
public:
	FileMapTagItem(int tag=0);
	FileMapTagItem(const PublishTarget& tag);

	~FileMapTagItem();
	bool operator<(const FileMapTagItem& tagItem)const { return mDiffScore < tagItem.mDiffScore; }
	bool operator==(const FileMapTagItem& other) const { return mTag == other.mTag; }
public:
	const FileMapNameItem* Find(StringRef name)const;
	FileMapNameItem* Find(StringRef name);
	FileMapNameItem* FindOrCreate(StringRef name);

	bool Contains(StringRef name)const;
	FileMapNameItem* Remove(const StringRef& name);

	const FileMapOrderItem* FindOrderItem(const FileIdRef& fileId)const;
	FileMapOrderItem* FindOrderItem(const FileIdRef& fileId);
	FileMapOrderItem* FindOrCreateOrderItem(const FileIdRef& fileId);


	bool ContainsOrderItem(const FileIdRef& fileId)const;

	int DiffScore() const { return mDiffScore; }
	int UpdateDiffScore(const PublishTarget& tag);

	bool IsEmpty()const { return mItems.IsEmpty(); }
	const PublishTarget& Tag() const { return mTag; }
	void SetTag(PublishTarget val) { mTag = val; }

	FileMapNameItem* Add(const StringRef& name);
	bool RemoveOrderItems(const FileEntry& fileEntry);

	const Dictionary<HeapString, FileMapNameItem*>& Items() const { return mItems; }
	const Dictionary<HeapString, FileMapNameItem*>& MutableItems()  { return mItems; }

protected:
	Dictionary<HeapString, FileMapNameItem*> mItems;

	PublishTarget mTag;
	/*
	Int.MinValue: not match
	-1:	super match in anyway
	0:	perfect match
	>0:	diff
	*/
	int mDiffScore;
};

MEDUSA_END;