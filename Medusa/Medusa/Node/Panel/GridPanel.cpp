// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GridPanel.h"

MEDUSA_BEGIN;

GridPanel::GridPanel(StringRef name/*=StringRef::Empty*/):IPanel(name)
{
}

GridPanel::~GridPanel(void)
{

}

bool GridPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

MEDUSA_IMPLEMENT_RTTI(GridPanel, IPanel);

MEDUSA_END;
