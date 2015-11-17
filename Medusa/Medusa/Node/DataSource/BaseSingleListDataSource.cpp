// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseSingleListDataSource.h"
#include "Node/ItemTemplate/IItemTemplate.h"

MEDUSA_BEGIN;


BaseSingleListDataSource::BaseSingleListDataSource():mItemTemplate(nullptr)
{
	
}

BaseSingleListDataSource::~BaseSingleListDataSource( void )
{
	SAFE_DELETE(mItemTemplate);
}

void BaseSingleListDataSource::SetItemTemplate(IItemTemplate* val)
{
	SAFE_ASSIGN(mItemTemplate,val);
}

MEDUSA_IMPLEMENT_RTTI(BaseSingleListDataSource,IListDataSource);

MEDUSA_END;
