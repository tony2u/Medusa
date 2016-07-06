// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "EditBoxLayer.h"


EditBoxLayer::EditBoxLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{



}

EditBoxLayer::~EditBoxLayer(void)
{
}

bool EditBoxLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());


	INode* sprite=NodeFactory::Instance().CreateSingleLineEditBox(msize(500,180), FontId("PaperBlack.ttf",96),L"ABC");
	sprite->SetDock(DockPoint::MiddleCenter);
	sprite->SetAnchor(0.5f, 0.5f);
	
	AddChild(sprite);

	return true;
}




MEDUSA_IMPLEMENT_NODE(EditBoxLayer);

