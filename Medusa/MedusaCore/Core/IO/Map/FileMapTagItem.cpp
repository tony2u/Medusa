// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileMapTagItem.h"
#include "Core/IO/FileId.h"
#include "Core/IO/Storage/FileEntry.h"

MEDUSA_BEGIN;


FileMapTagItem::FileMapTagItem(int tag/*=0*/)
	:mTag(tag)
{
	mDiffScore = 0;
}

FileMapTagItem::FileMapTagItem(const PublishTarget& tag) :mTag(tag)
{
	mDiffScore = 0;
}


FileMapTagItem::~FileMapTagItem()
{
	SAFE_DELETE_DICTIONARY_VALUE(mItems);
}


const FileMapNameItem* FileMapTagItem::Find(StringRef name) const
{
	return mItems.GetOptional(name, nullptr);
}
FileMapNameItem* FileMapTagItem::Find(StringRef name)
{
	return mItems.GetOptional(name, nullptr);
}

FileMapNameItem* FileMapTagItem::FindOrCreate(StringRef name)
{
	FileMapNameItem* item= mItems.GetOptional(name, nullptr);
	if (item==nullptr)
	{
		item = new FileMapNameItem(name);
		item->SetParent(this);
		mItems.Add(name, item);
	}

	return item;

}

const FileMapOrderItem* FileMapTagItem::FindOrderItem(const FileIdRef& fileId) const
{
	const FileMapNameItem* nameItem = mItems.GetOptional(fileId.Name, nullptr);
	RETURN_NULL_IF_NULL(nameItem);
	return nameItem->Find((uint)fileId.Order);
}

FileMapOrderItem* FileMapTagItem::FindOrderItem(const FileIdRef& fileId)
{
	FileMapNameItem* nameItem = mItems.GetOptional(fileId.Name, nullptr);
	RETURN_NULL_IF_NULL(nameItem);
	return nameItem->Find((uint)fileId.Order);
}



FileMapOrderItem* FileMapTagItem::FindOrCreateOrderItem(const FileIdRef& fileId)
{
	FileMapNameItem* nameItem= FindOrCreate(fileId.Name);
	return nameItem->FindOrCreate(fileId.Order);
}

bool FileMapTagItem::ContainsOrderItem(const FileIdRef& fileId) const
{
	const FileMapNameItem* nameItem = mItems.GetOptional(fileId.Name, nullptr);
	RETURN_FALSE_IF_NULL(nameItem);
	return nameItem->Contains((uint)fileId.Order);
}


bool FileMapTagItem::Contains(StringRef name) const
{
	return mItems.ContainsKey(name);
}

FileMapNameItem* FileMapTagItem::Remove(const StringRef& name)
{
	return mItems.RemoveOtherKeyOptional(name, name.HashCode(), nullptr);
}

int FileMapTagItem::UpdateDiffScore(const PublishTarget& tag)
{
	mDiffScore = mTag.GetDiffScore(tag);
	return mDiffScore;
}


FileMapNameItem* FileMapTagItem::Add(const StringRef& name)
{
	FileMapNameItem* item = new FileMapNameItem(name);
	mItems.Add(name, item);
	item->SetName(name);
	item->SetParent(this);
	return item;
}

bool FileMapTagItem::RemoveOrderItems(const FileEntry& fileEntry)
{
	FileId fileId = FileId::ParseFrom(fileEntry.Name());
	FileMapNameItem* nameItem=mItems.GetOptional(fileId.Name, nullptr);
	if (nameItem->RemoveOrderItems(fileEntry))
	{
		if (!nameItem->IsEmpty())
		{
			mItems.RemoveKey(fileId.Name);
			delete nameItem;
		}
		return true;
	}

	return false;
}


MEDUSA_END;