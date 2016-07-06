// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "CanvasPanel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

CanvasPanel::~CanvasPanel(void)
{

}


bool CanvasPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	RETURN_FALSE_IF(mIsCollapsed);

	for (auto child : mNodes)
	{
		child->ArrangeRecursively(Rect2F::Zero);
	}

	return true;
}

MEDUSA_IMPLEMENT_NODE(CanvasPanel);

MEDUSA_END;
