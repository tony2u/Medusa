// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "UniformGridPanel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


UniformGridPanel::~UniformGridPanel(void)
{

}

bool UniformGridPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

MEDUSA_IMPLEMENT_NODE(UniformGridPanel);

MEDUSA_END;
