// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "AnimationFeatureLayer.h"
#include "SingleTextureFrameAnimationLayer.h"
#include "TexturesAnimationLayer.h"
#include "TextureAtlasFrameAnimationLayer.h"
#include "SpineAnimationLayer.h"



AnimationFeatureLayer::AnimationFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<SingleTextureFrameAnimationLayer>();
	Register<TexturesAnimationLayer>();

	Register<TextureAtlasFrameAnimationLayer>();
	Register<SpineAnimationLayer>();
}

AnimationFeatureLayer::~AnimationFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(AnimationFeatureLayer, BaseFeatureLayer, StringRef::Empty);

