// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IListDataSource.h"

MEDUSA_BEGIN;

class BaseMultipleListDataSource:public IListDataSource
{
	MEDUSA_DECLARE_RTTI;

public:
	BaseMultipleListDataSource();
	virtual ~BaseMultipleListDataSource(void);

	virtual bool IsFixedType()const override{return false;}

protected:
	List<IItemTemplate*> mItemTemplates;

};

MEDUSA_END;
