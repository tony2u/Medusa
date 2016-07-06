// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Object/SingleObjectPool.h"
#include "Core/Pattern/Singleton.h"
#include "LogMessage.h"
#include "Core/Threading/Mutex.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Pattern/Share.h"


MEDUSA_BEGIN;


template<typename T>
class TLogMessagePool :public Singleton<TLogMessagePool<T>>
{
	TLogMessagePool(){}
	~TLogMessagePool(void)
	{
		mItems.Clear();
	}
	friend class Singleton<TLogMessagePool<T>>;
	using ItemType = Share<TLogMessage<T>>;
	using MessageType = TLogMessage<T>;

public:
	void Clear()
	{
		ScopedLock lock(mMutex);
		mItems.Clear();
	}

	ItemType Create(LogLevel type = LogLevel::Info)
	{
		ScopedLock lock(mMutex);
		if (!mItems.IsEmpty())
		{
			ItemType obj = mItems.Last();
			mItems.RemoveLast();
			obj->Prepare(type);
			return obj;	//ref 1
		}
		return new MessageType(type);	//ref 1
	}

	void Recycle(const ItemType& obj)
	{
		if (!obj->IsShared())	//only recycle on last ref
		{
			ScopedLock lock(mMutex);
			mItems.Append(obj);	//keep ref
			obj->Recycle();
		}

	}
protected:
	List<ItemType> mItems;
	Mutex mMutex;
};


//[PRE_DECLARE_BEGIN]
typedef TLogMessagePool<char> LogMessagePool;
typedef TLogMessagePool<wchar_t> WLogMessagePool;
//[PRE_DECLARE_END]

MEDUSA_END;
