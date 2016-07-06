// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"
#include "BaseSingleListDataSource.h"

MEDUSA_BEGIN;

class StringListDataSource:public BaseSingleListDataSource
{
	MEDUSA_RTTI(StringListDataSource,BaseSingleListDataSource);

public:
	StringListDataSource(const List<WHeapString>& strItems,bool isSingleLine=true);
	virtual ~StringListDataSource(void);

	virtual size_t Count()const override{return mItems.Count();}
	virtual int GetItemType(size_t index)const override{ return 0; }
	virtual bool IsFixedSize()const override{return true;}

	WStringRef GetString(size_t index)const;

	void Add(WStringRef str);
	void Update(size_t index, WStringRef str);
	void RemoveAt(size_t index);
	void Clear();
protected:
	List<WHeapString> mItems;
};

MEDUSA_END;
