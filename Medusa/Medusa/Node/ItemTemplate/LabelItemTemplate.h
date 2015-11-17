// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IItemTemplate.h"
#include "Resource/Font/FontId.h"

MEDUSA_BEGIN;

class LabelItemTemplate:public IItemTemplate
{
public:
	LabelItemTemplate(bool isSingleLine=true);
	virtual ~LabelItemTemplate(void);

	virtual Size2F CalculateItemSize(const IListDataSource& dataSource, size_t index, const Size2F& limitSize)const override;
	virtual INode* CreateItem(const IListDataSource& dataSource, size_t index, const Size2F& limitSize)override;
	virtual bool ReloadItem(INode* node, const IListDataSource& dataSource, size_t index, const Size2F& limitSize)override;

public:
	const FontId& GetFontId() const { return mFontId; }
	FontId& MutableFontId()  { return mFontId; }

	Alignment GetAlignment() const { return mAlignment; }
	void SetAlignment(Alignment val) { mAlignment = val; }


	bool IsStatic() const { return mIsStatic; }
	void SetIsStatic(bool val) { mIsStatic = val; }

protected:
	HeapString mFontName;
	FontId mFontId;
	Alignment mAlignment=Alignment::LeftBottom;
	bool mIsSingleLine = true;
	bool mIsStatic=true;
	
};

MEDUSA_END;
