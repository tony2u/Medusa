// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "NodeButtonLayer.h"


NodeButtonLayer::NodeButtonLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{

}

NodeButtonLayer::~NodeButtonLayer(void)
{
}

bool NodeButtonLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	NodeButton* button=NodeFactory::Instance().CreateNodeButton("Close.png","CloseSelected.png");
	button->SetDock(DockPoint::MiddleCenter);
	button->SetAnchorPoint(AnchorPoint::MiddleCenter);
	button->SelectedNode()->SetScale(0.8f);
	AddChild(button);

	button->OnTap+=Bind(&NodeButtonLayer::OnTap,this);

	return true;
}


void NodeButtonLayer::OnTap(INode* sender,TapGestureEventArg& e)
{
	Log::FormatInfo("Tap");
}



MEDUSA_IMPLEMENT_LAYER(NodeButtonLayer, BaseCaseLayer, StringRef::Empty, StringRef::Empty);

