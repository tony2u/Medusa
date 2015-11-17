// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IPanel.h"

MEDUSA_BEGIN;

IPanel::IPanel(StringRef name/*=StringRef::Empty*/):INode(name)
{
	SetSizeToContent(SizeToContent::WidthAndHeight);
}

IPanel::~IPanel(void)
{
}
MEDUSA_IMPLEMENT_RTTI(IPanel, INode);

MEDUSA_END;
