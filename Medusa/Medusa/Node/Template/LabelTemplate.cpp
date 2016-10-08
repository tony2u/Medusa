// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "LabelTemplate.h"
#include "Node/INode.h"
#include "Resource/Font/FontFactory.h"
#include "Resource/Font/TextLayout/TextLayouter.h"
#include "Node/NodeFactory.h"
#include "Node/Control/Label/ILabel.h"

MEDUSA_BEGIN;


LabelTemplate::LabelTemplate(bool isSingleLine/*=true*/)
	:mFontId("arial22.fnt"),
	mIsSingleLine(isSingleLine)
{

}

LabelTemplate::~LabelTemplate(void)
{

}


Size2F LabelTemplate::Measure(const WHeapString& data, const Size2F& limitSize /*= Size2F::Zero*/) const
{
	auto font = FontFactory::Instance().Create(mFontId);

	if (mIsSingleLine)
	{
		return TextLayouter::GetSingleLineSize(*font, data);
	}
	else
	{
		return TextLayouter::GetMultipleLineSize(*font, data, limitSize);
	}
}

INode* LabelTemplate::Load(const WHeapString& data, const Size2F& limitSize /*= Size2F::Zero*/, INode* reloadNode /*= nullptr*/)const
{
	if (reloadNode==nullptr)
	{
		if (mIsSingleLine)
		{
			reloadNode= NodeFactory::Instance().CreateSingleLineLabel(mFontId, data, mAlignment, limitSize);
		}
		else
		{
			reloadNode= NodeFactory::Instance().CreateMultipleLineLabel(mFontId, data, mAlignment, limitSize);
		}
	}
	else
	{
		ILabel* label = (ILabel*)reloadNode;

		Size2U newLimitSize((uint)limitSize.Width, (uint)limitSize.Height);
		label->SetRestrictSize(newLimitSize);
		label->SetString(data);
	}
	OnSetupNode(reloadNode);
	return reloadNode;
}


MEDUSA_END;
