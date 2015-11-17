// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"


MEDUSA_BEGIN;


template<typename T>
class Sweeper
{
public:
	virtual ~Sweeper(void)
	{
		Release();
	}
public:
	void Add(T item)
	{
#ifdef MEDUSA_SAFE_CHECK
		if (mItems.Contains(item))
		{
			OnAddFailed(item);
			return;
		}
#endif

		mItems.Add(item);
	}

	void Release()
	{
		RETURN_IF_EMPTY(mItems);
		RETURN_IF_FALSE(OnBeforeRelease());	//give a chance to release all in one time

		FOR_EACH_ITEM(mItems, OnRelease);
		mItems.Clear();
	}
protected:
#ifdef MEDUSA_SAFE_CHECK
	virtual void OnAddFailed(T item)const {}
#endif

	virtual bool OnBeforeRelease() { return true; }
	virtual void OnRelease(T item)const {}
protected:
	List<T> mItems;

};

MEDUSA_END;
