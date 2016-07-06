// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StackPanel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

StackPanel::StackPanel(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IPanel(name,e),
	mItemFixedSize(Size2F::Zero)
{
}

StackPanel::~StackPanel(void)
{

}

bool StackPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

MEDUSA_IMPLEMENT_NODE(StackPanel);

MEDUSA_END;
