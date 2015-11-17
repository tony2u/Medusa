// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Stack.h"

MEDUSA_BEGIN;
template <typename T>
class ObjectStack
{
public:
	ObjectStack() {}
	virtual ~ObjectStack() { Clear(); }
public:
	bool IsEmpty()const { return Count() == 0; }
	size_t Count() const { return mItems.Count(); }
	const Stack<T*>& Items()const { return mItems; }
public:
	void Clear()
	{
		SAFE_DELETE_COLLECTION(mItems);
	}

	T* Current()const { return mItems.TopOr(nullptr); }

	void Push(T* item) { mItems.Push(item); }
	T* Pop() { mItems.PopOr(nullptr); }
	T* ReplaceTo(T* item)
	{
		T* outOriginal = nullptr;
		mItems.Replace(item, outOriginal);
		return outOriginal;
	}
protected:
	Stack<T*> mItems;
};
MEDUSA_END;