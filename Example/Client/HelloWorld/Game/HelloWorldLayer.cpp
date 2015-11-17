// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "HelloWorldLayer.h"
#include "Core/Profile/ProfileSample.h"
#include "Node/Panel/PanelFactory.h"


HelloWorldLayer::HelloWorldLayer(StringRef name/*=StringRef::Empty*/,const IEventArg& e/*=IEventArg::Empty*/):ILayer(name,e)
{

	

}

HelloWorldLayer::~HelloWorldLayer(void)
{
}

bool HelloWorldLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(ILayer::Initialize());
	auto* sprite=NodeFactory::Instance().CreateQuadSprite("HelloWorld.png");
	sprite->SetAnchorPoint(AnchorPoint::MiddleCenter);
	sprite->SetDock(DockPoint::MiddleCenter);
	AddChild(sprite);
	

	return true;
}


MEDUSA_IMPLEMENT_LAYER(HelloWorldLayer,ILayer,StringRef::Empty);
