// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IPanel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

IPanel::IPanel(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:INode(name,e)
{
	SetSizeToContent(SizeToContent::WidthAndHeight);
}

IPanel::~IPanel(void)
{
}


MEDUSA_END;
