// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "CanvasPanel.h"
MEDUSA_BEGIN;

CanvasPanel::CanvasPanel(StringRef name/*=StringRef::Empty*/):IPanel(name)
{
}

CanvasPanel::~CanvasPanel(void)
{

}


bool CanvasPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	RETURN_FALSE_IF(mIsCollapsed);

	FOR_EACH_COLLECTION(i,mNodes)
	{
		INode* child=*i;
		child->ArrangeRecursively(Rect2F::Zero);
	}

	return true;
}

MEDUSA_IMPLEMENT_RTTI(CanvasPanel, IPanel);

MEDUSA_END;
