// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IDataSource.h"
#include "Core/Collection/List.h"
#include "Geometry/Size2.h"
#include "Geometry/Range.h"

MEDUSA_BEGIN;

class IListDataSource:public IDataSource
{
	MEDUSA_DECLARE_RTTI;

public:
	typedef Event<void(size_t index)> ItemAddedEvent;
	typedef Event<void(size_t index)> ItemRemovedEvent;
	typedef Event<void(size_t index, size_t length)> ItemUpdatedEvent;

	ItemAddedEvent OnItemAdded;
	ItemRemovedEvent OnItemRemoved;
	ItemUpdatedEvent OnItemUpdated;
public:
	IListDataSource();
	virtual ~IListDataSource(void);

	virtual size_t Count()const=0;
	virtual int GetItemType(size_t index)const = 0;
	virtual bool IsFixedType()const=0;
	virtual bool IsFixedSize()const=0;



	virtual Size2F CalculateItemSize(size_t index, const Size2F& limitSize);
	virtual INode* CreateItem(size_t index, const Size2F& limitSize);
	virtual bool ReloadItem(INode* node, size_t index, const Size2F& limitSize);

	virtual void Commit() override;
protected:
	virtual IItemTemplate* GetItemTemplate(size_t index)const = 0;
	void FireItemUpdatedEvent(size_t index, size_t length);
	void FireItemAddedEvent(size_t index);
	void FireItemRemovedEvent(size_t index);
	virtual void FireDataChangedEvent() override;

protected:
	RangeS mDirtyRange;
};

MEDUSA_END;
