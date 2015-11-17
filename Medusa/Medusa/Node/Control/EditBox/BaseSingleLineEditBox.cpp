// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseSingleLineEditBox.h"
#include "Node/NodeFactory.h"
#include "Node/Control/Label/ILabel.h"


MEDUSA_BEGIN;


BaseSingleLineEditBox::BaseSingleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text /*= WStringRef::Empty*/, Alignment alignment /*= Alignment::LeftBottom*/)
	:IEditBox(name, size, fontId, text, alignment)
{
	mTextLabel = NodeFactory::Instance().CreateSingleLineLabel(fontId, text, alignment, size);
	mTextLabel->EnableManaged();
	AddChild(mTextLabel);

	mPlaceHolderLabel = NodeFactory::Instance().CreateSingleLineLabel(fontId, WStringRef::Empty, alignment, size, true);
	mPlaceHolderLabel->EnableManaged();

	AddChild(mPlaceHolderLabel);

	OnUpdateStatus();

}

BaseSingleLineEditBox::~BaseSingleLineEditBox(void)
{

}

MEDUSA_IMPLEMENT_RTTI(BaseSingleLineEditBox, IEditBox);

MEDUSA_END;
