// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Resource/IResourceFactory.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

template<typename T>
class BaseResourceFactory:public IResourceFactory<FileIdRef,T*>
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
		FOR_EACH_COLLECTION(i,mItems)
		{
			FileIdRef fileId=i->Key.ToRef();
			T* item=i->Value;
			if (!item->IsShared())
			{
				unusedKeys.Add(fileId);
			}
		}

		RETURN_IF_EMPTY(unusedKeys);
		FOR_EACH_COLLECTION(i,unusedKeys)
		{
			Remove(*i);
		}
	}

	virtual void Clear()override
	{
		RETURN_IF_EMPTY(mItems);
		SAFE_RELEASE_COLLECTION(mCacheItems);

		SAFE_RELEASE_DICTIONARY_VALUE(mItems);
	}

	virtual bool Remove(const FileIdRef& fileId)override
	{
		T* item=mItems.RemoveOtherKeyWithValueReturned(fileId,fileId.HashCode(),nullptr);
		RETURN_FALSE_IF_NULL(item);
		item->Release();
		return true;
	}

	virtual T* Find(const FileIdRef& fileId)const override
	{
		if (!fileId.IsValid())
		{
			return nullptr;
		}
		return mItems.TryGetValueWithFailedByOtherKey(fileId,fileId.HashCode(),nullptr);
	}

	virtual bool Add(T* val, ResourceShareType shareType = ResourceShareType::Share)override
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
					val->Retain();
					return true;
				}
				break;
			case ResourceShareType::ShareAndCache:
				if (mItems.TryAdd(val->GetFileId(), val))
				{
					val->Retain();
					mCacheItems.Add(val);
					val->Retain();

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
		SAFE_RELEASE_COLLECTION(mCacheItems);
		Shrink();
	}

protected:
	Dictionary<FileId,T*> mItems;
	List<T*> mCacheItems;
};

MEDUSA_END;