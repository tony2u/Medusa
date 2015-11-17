// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StringListDataSource.h"
#include "Node/ItemTemplate/LabelItemTemplate.h"

MEDUSA_BEGIN;


StringListDataSource::StringListDataSource(const List<WHeapString>& strItems,bool isSingleLine/*=true*/)
	:mItems(strItems)
{
	mItemTemplate=new LabelItemTemplate(isSingleLine);
}

StringListDataSource::~StringListDataSource( void )
{
}

WStringRef StringListDataSource::GetString(size_t index) const
{
	return mItems[index];
}

void StringListDataSource::Add(WStringRef str)
{
	mItems.Add(str);
	FireItemAddedEvent(mItems.Count()-1);
}

void StringListDataSource::Update(size_t index, WStringRef str)
{
	mItems[index]=str;
	FireItemUpdatedEvent(index,1);

}

void StringListDataSource::RemoveAt(size_t index)
{
	mItems.RemoveAt(index);
	FireItemRemovedEvent(index);
}

void StringListDataSource::Clear()
{
	mItems.Clear();
	FireDataChangedEvent();
}

MEDUSA_IMPLEMENT_RTTI(StringListDataSource,BaseSingleListDataSource);

MEDUSA_END;
