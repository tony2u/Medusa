// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "DockPanel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


DockPanel::~DockPanel(void)
{

}

bool DockPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

MEDUSA_IMPLEMENT_NODE(DockPanel);

MEDUSA_END;
