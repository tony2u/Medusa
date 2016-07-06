// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "LabelItemTemplate.h"
#include "Node/INode.h"
#include "Resource/Font/FontFactory.h"
#include "Resource/Font/TextLayout/TextLayouter.h"
#include "Node/NodeFactory.h"
#include "Node/Control/Label/ILabel.h"
#include "Node/DataSource/StringListDataSource.h"

MEDUSA_BEGIN;


LabelItemTemplate::LabelItemTemplate(bool isSingleLine/*=true*/)
	:IItemTemplate(),
	mFontId("arial22.fnt"),
	mIsSingleLine(isSingleLine)
{

}

LabelItemTemplate::~LabelItemTemplate( void )
{

}


Size2F LabelItemTemplate::CalculateItemSize(const IListDataSource& dataSource, size_t index, const Size2F& limitSize) const
{
	const StringListDataSource& stringDataSource=(const StringListDataSource&)dataSource;
	WStringRef str=stringDataSource.GetString(index);
	auto font=FontFactory::Instance().Create(mFontId);

	if (mIsSingleLine)
	{
		return TextLayouter::GetSingleLineSize(*font,str);
	}
	else
	{
		return TextLayouter::GetMultipleLineSize(*font,str,limitSize);
	}
}

INode* LabelItemTemplate::CreateItem(const IListDataSource& dataSource, size_t index, const Size2F& limitSize)
{
	const StringListDataSource& stringDataSource=(const StringListDataSource&)dataSource;
	WStringRef str=stringDataSource.GetString(index);

	if (mIsSingleLine)
	{
		return NodeFactory::Instance().CreateSingleLineLabel(mFontId,str,mAlignment,limitSize);
	}
	else
	{
		return NodeFactory::Instance().CreateMultipleLineLabel(mFontId,str,mAlignment,limitSize);
	}
}

bool LabelItemTemplate::ReloadItem(INode* node, const IListDataSource& dataSource, size_t index, const Size2F& limitSize)
{
	ILabel* label=(ILabel*)node;
	const StringListDataSource& stringDataSource=(const StringListDataSource&)dataSource;
	WStringRef str=stringDataSource.GetString(index);
	label->SetString(str);
	
	Size2U newLimitSize((uint)limitSize.Width,(uint)limitSize.Height);
	label->SetRestrictSize(newLimitSize);

	return true;
}

MEDUSA_END;
