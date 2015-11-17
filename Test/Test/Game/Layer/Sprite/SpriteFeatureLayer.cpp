// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "SpriteFeatureLayer.h"
#include "SpriteLayer.h"
#include "NineGridSpriteLayer.h"
#include "AtlasSpriteLayer.h"

SpriteFeatureLayer::SpriteFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<SpriteLayer>();
	Register<NineGridSpriteLayer>();
	Register<AtlasSpriteLayer>();


}

SpriteFeatureLayer::~SpriteFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(SpriteFeatureLayer, BaseFeatureLayer, StringRef::Empty);

