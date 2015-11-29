// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TextureAtlasFrameAnimationLayer.h"


TextureAtlasFrameAnimationLayer::TextureAtlasFrameAnimationLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{

}

TextureAtlasFrameAnimationLayer::~TextureAtlasFrameAnimationLayer(void)
{
}

bool TextureAtlasFrameAnimationLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());
	
	{
		ITimeline* timeline = TimelineFactory::Instance().CreateRenderingObjectTimelineFromTextureAtlasDefault("MeteorFall", TextureAtlasFileFormat::Spine, 1, Color4F::White, 24.f, true);
		Sprite* sprite = new Sprite("MeteorFall");
		sprite->SetSize(512.f, 512.f);
		sprite->SetDock(DockPoint::Percent);
		sprite->SetRelativePosition(mpp(0.25,0.5f));
		sprite->SetAnchor(0.5f, 0.5f);
		AddChild(sprite);
		sprite->RunAction(timeline);
	}
	{
		ITimeline* timeline = TimelineFactory::Instance().CreateRenderingObjectTimelineFromTextureAtlasDefault("MeteorExplode", TextureAtlasFileFormat::Spine, 1, Color4F::White, 24.f, true);
		Sprite* sprite = new Sprite("MeteorExplode");
		sprite->SetSize(512.f, 512.f);
		sprite->SetDock(DockPoint::Percent);
		sprite->SetRelativePosition(mpp(0.75, 0.5f));
		sprite->SetAnchor(0.5f, 0.5f);
		AddChild(sprite);
		sprite->RunAction(timeline);
	}

	return true;
}




MEDUSA_IMPLEMENT_LAYER(TextureAtlasFrameAnimationLayer, BaseCaseLayer, StringRef::Empty);

