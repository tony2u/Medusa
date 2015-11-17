// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseMultipleListDataSource.h"
#include "Node/ItemTemplate/IItemTemplate.h"

MEDUSA_BEGIN;


BaseMultipleListDataSource::BaseMultipleListDataSource()
{
	
}

BaseMultipleListDataSource::~BaseMultipleListDataSource( void )
{
	SAFE_DELETE_COLLECTION(mItemTemplates);
}

MEDUSA_IMPLEMENT_RTTI(BaseMultipleListDataSource,IListDataSource);

MEDUSA_END;
