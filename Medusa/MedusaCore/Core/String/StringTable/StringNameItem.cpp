// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

//SIREN_BODY_INCLUDE_BEGIN
#include "StringNameItem.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Log/Log.h"


MEDUSA_BEGIN;

StringNameItem::StringNameItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
	mFirstItem = nullptr;
}
StringNameItem::StringNameItem(uint order, const StringRef& filePath)
{
	mItems.Add(order, filePath);
	mFirstItem = mItems.MutableFirst();

}

StringNameItem::StringNameItem(const StringRef& name)
	: mName(name), mFirstItem(nullptr)
{

}

StringNameItem::~StringNameItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}


bool StringNameItem::Contains(uint order) const
{
	return mItems.ContainsKey(order);
}

bool StringNameItem::Initialize()
{
	mFirstItem = mItems.MutableFirst();

	return true;
}

bool StringNameItem::Add(uint order, const StringRef& val)
{
	if (mFirstItem != nullptr)
	{
		RETURN_FALSE_IF_EQUAL(mFirstItem->Key, order);
		RETURN_FALSE_IF_EQUAL(mFirstItem->Value, val);

		if (mItems.ContainsKey(order))
		{
			return false;
		}

		mItems.Add(order, val);
	}
	else
	{
		mItems.Add(order, val);
		mFirstItem = mItems.MutableFirst();
	}

	return true;


}


const HeapString* StringNameItem::Find(uint order) const
{
	return mItems.TryGetValue(order);
}


//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(StringNameItem, 14);
SIREN_PROPERTY_METADATA_STRUCT(0, StringNameItem, Items, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;