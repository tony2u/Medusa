// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "BaseCaseLayer.h"


BaseCaseLayer::BaseCaseLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/)
	:ILayer(name, e)
{
	
}

BaseCaseLayer::~BaseCaseLayer(void)
{
}

bool BaseCaseLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(ILayer::Initialize());

	HeapString title = Class().Name();
	title.RemoveLast("Layer");

	ILabel* label = NodeFactory::Instance().CreateSingleLineLabel(FontId("arial22.fnt"), title, Alignment::LeftBottom, Size2U::Zero, true);
	label->SetDock(DockPoint::MiddleTop);
	label->SetAnchorPoint(AnchorPoint::MiddleTop);
	label->SetDepth(9999);
	AddChild(label);


	return true;
}



MEDUSA_IMPLEMENT_NODE(BaseCaseLayer);

