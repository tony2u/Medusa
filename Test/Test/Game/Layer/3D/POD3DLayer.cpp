// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "POD3DLayer.h"


POD3DLayer::POD3DLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

POD3DLayer::~POD3DLayer(void)
{
}

bool POD3DLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	auto* shape1 = NodeFactory::Instance().CreatePODSprite("Scene.pod");
	//shape1->SetAnchor(0.5f, 0.5f);
	//shape1->SetDock(DockPoint::MiddleCenter);
	AddChild(shape1);

	return true;
}




MEDUSA_IMPLEMENT_LAYER(POD3DLayer, BaseCaseLayer, StringRef::Empty);

