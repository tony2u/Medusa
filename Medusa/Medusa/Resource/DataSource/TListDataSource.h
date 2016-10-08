// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IDataSource.h"
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

template<typename T, class TCompare = EqualCompare >
class TListDataSource :public IDataSource
{
public:
	Event<void(size_t index)> OnItemAdded;
	Event<void(size_t index)> OnItemRemoved;
	Event<void(size_t index)> OnItemUpdated;
public:
	using IDataSource::IDataSource;
	TListDataSource(const List<T, TCompare>& items, const FileIdRef& fileId = FileIdRef::Empty)
		:mItems(items), IDataSource(fileId)
	{

	}

public:
	bool HasMultipleTag()const { return mHasMultipleTag; }
	void EnableMultipleTag(bool val) { mHasMultipleTag = val; }

public:
	virtual int GetTemplateTag(size_t index)const { return 0; }
	size_t Count()const { return mItems.Count(); }

	const T& At(size_t index)const
	{
		return mItems[index];
	}

	void Add(const T& val)
	{
		mItems.Add(val);
		OnItemAdded(mItems.Count() - 1);
	}

	void Insert(size_t index, const T& val)
	{
		mItems.Insert(index, val);
		OnItemAdded(index);
	}

	void Update(size_t index)
	{
		mItems[index] = val;
		OnItemUpdated(index);
	}
	void RemoveAt(size_t index)
	{
		mItems.RemoveAt(index);
		OnItemRemoved(index);
	}
	void Clear()
	{
		mItems.Clear();
		OnTotalChanged();
	}
protected:
	List<T, TCompare> mItems;
	bool mHasMultipleTag = false;
};


//[PRE_DECLARE_BEGIN]
typedef  TListDataSource<WHeapString, EqualCompare> WStringListDataSource;
typedef  TListDataSource<FileId, EqualCompare> FileIdListDataSource;
//[PRE_DECLARE_END]

MEDUSA_END;
