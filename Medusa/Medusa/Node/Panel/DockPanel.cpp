// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "DockPanel.h"

MEDUSA_BEGIN;

DockPanel::DockPanel(StringRef name/*=StringRef::Empty*/):IPanel(name)
{
}

DockPanel::~DockPanel(void)
{

}

bool DockPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

MEDUSA_IMPLEMENT_RTTI(DockPanel, IPanel);

MEDUSA_END;
