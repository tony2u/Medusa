// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IListDataSource.h"

MEDUSA_BEGIN;

class BaseSingleListDataSource:public IListDataSource
{
	MEDUSA_DECLARE_RTTI;

public:
	BaseSingleListDataSource();
	virtual ~BaseSingleListDataSource(void);

	virtual bool IsFixedType()const override{return true;}

	IItemTemplate* ItemTemplate() const { return mItemTemplate; }
	void SetItemTemplate(IItemTemplate* val);

protected:
	virtual IItemTemplate* GetItemTemplate(size_t index)const override{ return mItemTemplate; }
protected:
	IItemTemplate* mItemTemplate;
	
};

MEDUSA_END;
