// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "NineGridSpriteLayer.h"


NineGridSpriteLayer::NineGridSpriteLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

NineGridSpriteLayer::~NineGridSpriteLayer(void)
{
}

bool NineGridSpriteLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	INode* sprite=NodeFactory::Instance().CreateNineGridSprite(Size2F(200,400),"Dialog.png",ThicknessF(17.f,17.f,17.f,17.f));
	sprite->SetDock(DockPoint::MiddleCenter);
	sprite->SetAnchor(0.5f,0.5f);
	sprite->SetStretch(Stretch::Uniform);
	
	AddChild(sprite);

	return true;
}




MEDUSA_IMPLEMENT_LAYER(NineGridSpriteLayer, BaseCaseLayer, StringRef::Empty);

