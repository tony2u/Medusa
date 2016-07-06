// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "LabelButton.h"
#include "Node/Control/Label/ILabel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


LabelButton::LabelButton(ILabel* label, StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/) 
	:IButton(name, e),
	mLabel(label)
{
}

LabelButton::LabelButton(StringRef name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IButton(name, e)
{

}

LabelButton::~LabelButton(void)
{

}

bool LabelButton::Initialize()
{
	if (mLabel != nullptr)
	{
		mLabel->EnableManaged(true);
		mLabel->SetDock(DockPoint::MiddleCenter);
		mLabel->SetAnchorPoint(AnchorPoint::MiddleCenter);

		AddChild(mLabel);
		SetSize(mLabel->Size());	//default to normal size
	}

	return true;
}

MEDUSA_IMPLEMENT_NODE(LabelButton);

MEDUSA_END;
