// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IListDataSource.h"
#include "Node/ItemTemplate/IItemTemplate.h"

MEDUSA_BEGIN;


IListDataSource::IListDataSource( )
{
	
}

IListDataSource::~IListDataSource( void )
{

}


Size2F IListDataSource::CalculateItemSize(size_t index, const Size2F& limitSize)
{
	IItemTemplate* itemTemplate=GetItemTemplate(index);
	return itemTemplate->CalculateItemSize(*this,index,limitSize);
}

INode* IListDataSource::CreateItem(size_t index, const Size2F& limitSize)
{
	IItemTemplate* itemTemplate = GetItemTemplate(index);
	return itemTemplate->CreateItem(*this,index,limitSize);
}

bool IListDataSource::ReloadItem(INode* node, size_t index, const Size2F& limitSize)
{
	IItemTemplate* itemTemplate = GetItemTemplate(index);
	return itemTemplate->ReloadItem(node,*this,index,limitSize);
}


void IListDataSource::Commit()
{
	RETURN_IF_EMPTY(mDirtyRange);
	size_t count=mDirtyRange.Count();
	if (count>=Count())
	{
		OnDataChanged(*this);
	}
	else
	{
		OnItemUpdated(mDirtyRange.Min,count);
	}

	mDirtyRange.Reset();
	mIsChanging=false;
}

void IListDataSource::FireItemUpdatedEvent(size_t index, size_t length)
{
	if (mIsChanging)
	{
		mDirtyRange.ExpandRange(index,index+length);
	}
	else
	{
		OnItemUpdated(index,length);
	}
}

void IListDataSource::FireItemAddedEvent(size_t index)
{
	if (mIsChanging)
	{
		mDirtyRange.ExpandRangeFrom(index,Count()-1);
	}
	else
	{
		OnItemAdded(index);
	}
}

void IListDataSource::FireItemRemovedEvent(size_t index)
{
	if (mIsChanging)
	{
		mDirtyRange.ExpandRangeFrom(index,Count()-1);
	}
	else
	{
		OnItemRemoved(index);
	}
}


void IListDataSource::FireDataChangedEvent()
{
	if (mIsChanging)
	{
		mDirtyRange.Min=0;
		mDirtyRange.Max=Count()-1;
	}
	else
	{
		OnDataChanged(*this);
	}

}



MEDUSA_END;
