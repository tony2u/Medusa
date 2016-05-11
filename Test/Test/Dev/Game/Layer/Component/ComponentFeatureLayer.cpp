// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ComponentFeatureLayer.h"
#include "ParallaxComponentLayer.h"
#include "ScrollComponentLayer.h"
#include "ParallaxScrollComponentLayer.h"


ComponentFeatureLayer::ComponentFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<ParallaxComponentLayer>();
	Register<ScrollComponentLayer>();
	Register<ParallaxScrollComponentLayer>();




}

ComponentFeatureLayer::~ComponentFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(ComponentFeatureLayer, BaseFeatureLayer, StringRef::Empty, StringRef::Empty);

