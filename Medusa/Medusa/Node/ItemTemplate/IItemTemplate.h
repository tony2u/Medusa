// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Geometry/Size2.h"

MEDUSA_BEGIN;

class IItemTemplate
{
public:
	IItemTemplate();
	virtual ~IItemTemplate(void);

	virtual Size2F CalculateItemSize(const IListDataSource& dataSource, size_t index, const Size2F& limitSize)const = 0;
	virtual INode* CreateItem(const IListDataSource& dataSource, size_t index, const Size2F& limitSize) = 0;
	virtual bool ReloadItem(INode* node, const IListDataSource& dataSource, size_t index, const Size2F& limitSize) = 0;

};

MEDUSA_END;
