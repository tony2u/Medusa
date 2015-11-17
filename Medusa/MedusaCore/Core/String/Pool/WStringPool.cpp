// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "WStringPool.h"

MEDUSA_BEGIN;

WStringPool::~WStringPool()
{

}

bool WStringPool::Initialize()
{
	return true;
}

bool WStringPool::Uninitialize()
{
	mItems.Clear();
	return true;
}

WHeapString WStringPool::Create(const wchar_t* str, uint length)
{
	WStringRef key(str, length);
	{
		mLock.BeginRead();
		WHeapString* temp = mItems.TryGetByOther(key, key.HashCode());
		if (temp != nullptr)
		{
			mLock.EndRead();
			return *temp;
		}
		mLock.EndRead();
	}


	{
		mLock.BeginWrite();
		WHeapString& result = mItems.NewAdd(key, key.HashCode());
		result = key;
		mLock.EndWrite();
		return result;
	}
}

MEDUSA_END;
