// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"


MEDUSA_BEGIN;


template<typename T>
class SharableObjectFactory
{
	SharableObjectFactory() {}
	~SharableObjectFactory(void) {}
public:
	template<typename TItem>
	TItem* Create()
	{
		const RTTIClass* rttiClass = &TItem::ClassStatic();
		T* item=mItems.GetOptional(rttiClass, nullptr);
		if (item!=nullptr)
		{
			return (TItem*)item;
		}
		item = new TItem();
		mItems.Add(rttiClass, item);
		return item;
	}

	void Clear()
	{
		List<const RTTIClass*> unUsedItems;
		for(auto i: mItems)
		{
			T* item = i.Value;
			if (!item->IsShared())
			{
				unUsedItems.Add(i.Key);
				item->Release();
			}
		}

		for (auto i : unUsedItems)
		{
			mItems.RemoveKey(i);
		}
	}
protected:
	Dictionary<const RTTIClass*, T*> mItems;
};

MEDUSA_END;
