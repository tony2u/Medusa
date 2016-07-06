// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Resource/IResourceFactory.h"
#include "Core/IO/FileId.h"
#include "Core/Pattern/Share.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

template<typename T>
class BaseResourceFactory:public IResourceFactory<FileIdRef,T>
{
public:
	virtual ~BaseResourceFactory()
	{
		Clear();
	}
public:
	virtual void Shrink()override
	{
		RETURN_IF_EMPTY(mItems);
		List<FileIdRef> unusedKeys;
		for(auto& i:mItems)
		{
			FileIdRef fileId=i.Key.ToRef();
			auto& item=i.Value;
			if (!item->IsShared())
			{
				unusedKeys.Add(fileId);
			}
		}

		RETURN_IF_EMPTY(unusedKeys);
		for (auto& i : unusedKeys)
		{
			Remove(i);
		}
	}

	virtual void Clear()override
	{
		RETURN_IF_EMPTY(mItems);
		mCacheItems.Clear();
#ifdef MEDUSA_SAFE_CHECK
		for (auto& i:mItems)
		{
			auto& item = i.Value;
			if (item->IsShared())
			{
				Log::FormatError("Not zero ref count", item->RefCount());
			}
		}
#endif
		mItems.Clear();
	}

	virtual bool Remove(const FileIdRef& fileId)override
	{
		return mItems.RemoveOtherKey(fileId,fileId.HashCode());
	}

	virtual ItemType Find(const FileIdRef& fileId)const override
	{
		if (!fileId.IsValid())
		{
			return nullptr;
		}
		return mItems.GetOptionalByOtherKey(fileId,fileId.HashCode(),nullptr);
	}

	virtual bool Add(const ItemType& val, ResourceShareType shareType = ResourceShareType::Share)override
	{
		if (!val->GetFileId().IsValid())
		{
			return false;
		}

		RETURN_FALSE_IF_NULL(val);
		switch (shareType)
		{
			case ResourceShareType::Share:
				if (mItems.TryAdd(val->GetFileId(), val))
				{
					
					return true;
				}
				break;
			case ResourceShareType::ShareAndCache:
				if (mItems.TryAdd(val->GetFileId(), val))
				{
					mCacheItems.Add(val);
					return true;
				}

				break;
			default:
				return true;
		}
	
		return false;
	}

	virtual void ReleaseCache()  override
	{
		mCacheItems.Clear();
		Shrink();
	}

protected:
	Dictionary<FileId, ItemType> mItems;
	List<ItemType> mCacheItems;
};

MEDUSA_END;