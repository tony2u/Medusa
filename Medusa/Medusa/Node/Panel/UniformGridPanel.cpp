// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "UniformGridPanel.h"

MEDUSA_BEGIN;

UniformGridPanel::UniformGridPanel(StringRef name/*=StringRef::Empty*/):IPanel(name)
{
}

UniformGridPanel::~UniformGridPanel(void)
{

}

bool UniformGridPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

MEDUSA_IMPLEMENT_RTTI(UniformGridPanel, IPanel);

MEDUSA_END;
