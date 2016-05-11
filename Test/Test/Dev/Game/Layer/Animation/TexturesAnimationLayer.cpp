// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TexturesAnimationLayer.h"


TexturesAnimationLayer::TexturesAnimationLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{

}

TexturesAnimationLayer::~TexturesAnimationLayer(void)
{
}

bool TexturesAnimationLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	ITimeline* timeline= TimelineFactory::Instance().CreateRenderingObjectTimelineFromTextures("CellOpen", "CellOpen1.png", 15.f, true);
	Sprite* sprite = new Sprite("CellOpen");
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetDock(DockPoint::MiddleCenter);
	sprite->SetAnchor(0.5f, 0.5f);
	//sprite->SetScale(4.f);
	AddChild(sprite);

	sprite->RunAction(timeline);

	return true;
}




MEDUSA_IMPLEMENT_LAYER(TexturesAnimationLayer, BaseCaseLayer, StringRef::Empty, StringRef::Empty);

