// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "StringPool.h"

MEDUSA_BEGIN;

StringPool::~StringPool()
{

}

bool StringPool::Initialize()
{
	return true;
}

bool StringPool::Uninitialize()
{
	mItems.Clear();
	return true;
}

HeapString& StringPool::Create(const char* str, uint length)
{
	StringRef key(str, length);
	{
		mLock.BeginRead();
		HeapString* temp = mItems.TryGetByOther(key, key.HashCode());
		if (temp != nullptr)
		{
			mLock.EndRead();
			return *temp;
		}
		mLock.EndRead();
	}


	{
		mLock.BeginWrite();
		HeapString& result = mItems.NewAdd(key, key.HashCode());
		result = key;
		mLock.EndWrite();
		return result;
	}
}

MEDUSA_END;
