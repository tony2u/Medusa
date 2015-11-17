// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileMapNameItem.h"
#include "Core/Log/Log.h"



MEDUSA_BEGIN;


FileMapNameItem::FileMapNameItem(StringRef name/*=StringRef::Empty*/) 
	: mName(name), mFirstItem(nullptr)
{

}

FileMapNameItem::~FileMapNameItem()
{
	SAFE_DELETE_DICTIONARY_VALUE(mItems);
}


const FileMapOrderItem* FileMapNameItem::Find(uint order) const
{
	if (mFirstItem != nullptr)
	{
		if (mFirstItem->Order() == order)
		{
			return mFirstItem;
		}
	}

	return mItems.TryGetValueWithFailed(order, nullptr);
}

FileMapOrderItem* FileMapNameItem::Find(uint order)
{
	if (mFirstItem != nullptr)
	{
		if (mFirstItem->Order() == order)
		{
			return mFirstItem;
		}
	}

	return mItems.TryGetValueWithFailed(order, nullptr);
}

FileMapOrderItem* FileMapNameItem::FindOrCreate(uint order)
{
	FileMapOrderItem* orderItem= Find(order);
	if (orderItem==nullptr)
	{
		orderItem = new FileMapOrderItem(order);
		orderItem->SetParent(this);
		mItems.Add(order, orderItem);

		if (mFirstItem == nullptr)
		{
			mFirstItem = orderItem;
		}
	}
	return orderItem;

}

FileMapOrderItem* FileMapNameItem::Remove(uint order)
{
	RETURN_NULL_IF_NULL(mFirstItem);
	FileMapOrderItem* orderItem = mItems.TryGetValueWithFailed(order, nullptr);
	RETURN_NULL_IF_NULL(orderItem);
	mItems.RemoveKey(order);
	if (mFirstItem == orderItem)
	{
		mFirstItem = nullptr;
	}
	return orderItem;
}

bool FileMapNameItem::Contains(uint order) const
{
	return Find(order) != nullptr;
}


uint FileMapNameItem::Count() const
{
	return (uint)mItems.Count();
}


FileMapOrderItem* FileMapNameItem::Add(uint order)
{
	FileMapOrderItem* item = new FileMapOrderItem(order);
	mItems.Add(order, item);
	item->SetParent(this);
	if (mFirstItem == nullptr)
	{
		mFirstItem = item;
	}
	return item;
}

bool FileMapNameItem::RemoveOrderItems(const FileEntry& fileEntry)
{
	List<FileMapOrderItem*> resultItems;
	for (auto& item:mItems)
	{
		item.Value->RemoveFileEntry(fileEntry);
		if (!item.Value->IsValid())
		{
			resultItems.Add(item.Value);
		}
	}

	for (auto* item:resultItems)
	{
		mItems.RemoveKey(item->Order());
		delete item;
	}

	bool result = !resultItems.IsEmpty();
	resultItems.Clear();

	if (mItems.IsEmpty())
	{
		mFirstItem = nullptr;
	}
	else
	{
		mFirstItem = mItems.MutableFirst()->Value;
	}

	return result;
}



MEDUSA_END;