// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseSingleLineEditBox.h"
#include "Node/NodeFactory.h"
#include "Node/Control/Label/ILabel.h"
#include "Node/Control/Label/FntLabel.h"
#include "Node/NodeFactory.h"

MEDUSA_BEGIN;


BaseSingleLineEditBox::BaseSingleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text /*= WStringRef::Empty*/, Alignment alignment /*= Alignment::LeftBottom*/)
	:IEditBox(name)
{
	mTextLabel = NodeFactory::Instance().CreateSingleLineLabel(fontId, text, alignment, size);
	mTextLabel->EnableManaged();
	AddChild(mTextLabel);

	mPlaceHolderLabel = NodeFactory::Instance().CreateSingleLineLabel(fontId, WStringRef::Empty, alignment, size, true);
	mPlaceHolderLabel->EnableManaged();

	AddChild(mPlaceHolderLabel);

	OnUpdateStatus();

}

BaseSingleLineEditBox::BaseSingleLineEditBox(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IEditBox(name,e)
{
	mTextLabel = new FntLabel();
	mTextLabel->EnableManaged();
	AddChild(mTextLabel);
	mPlaceHolderLabel = new FntLabel();
	mPlaceHolderLabel->EnableManaged();
	AddChild(mPlaceHolderLabel);
}

BaseSingleLineEditBox::~BaseSingleLineEditBox(void)
{

}

bool BaseSingleLineEditBox::Initialize() 
{
	OnUpdateStatus();
	return true;
}

void BaseSingleLineEditBox::SetFontId(const FontId& val)
{
	mTextLabel->SetFontId(val);
	mPlaceHolderLabel->SetFontId(val);
}


MEDUSA_END;
