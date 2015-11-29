// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "SingleTextureFrameAnimationLayer.h"


SingleTextureFrameAnimationLayer::SingleTextureFrameAnimationLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{

}

SingleTextureFrameAnimationLayer::~SingleTextureFrameAnimationLayer(void)
{
}

bool SingleTextureFrameAnimationLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	ITimeline* timeline= TimelineFactory::Instance().CreateRenderingObjectTimelineFromSingleTexture("Walking", "StudentWalking.png", 4, 4, 4.f, true);
	Sprite* sprite = new Sprite("Walking");
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetDock(DockPoint::MiddleCenter);
	sprite->SetAnchor(0.5f, 0.5f);
	sprite->SetScale(4.f);
	AddChild(sprite);

	sprite->RunAction(timeline);

	return true;
}




MEDUSA_IMPLEMENT_LAYER(SingleTextureFrameAnimationLayer, BaseCaseLayer, StringRef::Empty);

