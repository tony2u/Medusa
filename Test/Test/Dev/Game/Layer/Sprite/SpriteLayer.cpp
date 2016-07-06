// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "SpriteLayer.h"


SpriteLayer::SpriteLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

SpriteLayer::~SpriteLayer(void)
{
}

bool SpriteLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	Sprite* sprite = NodeFactory::Instance().CreateSprite("Hearts.png");
	sprite->SetDock(DockPoint::MiddleCenter);
	sprite->SetAnchor(0.5f, 0.5f);
	AddChild(sprite);


	return true;
}




MEDUSA_IMPLEMENT_NODE(SpriteLayer);

