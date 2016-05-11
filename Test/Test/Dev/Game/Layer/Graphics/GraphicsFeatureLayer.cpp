// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "GraphicsFeatureLayer.h"
#include "BlendTestLayer.h"
#include "MaskLayer.h"


GraphicsFeatureLayer::GraphicsFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<BlendTestLayer>();
	Register<MaskLayer>();

}

GraphicsFeatureLayer::~GraphicsFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(GraphicsFeatureLayer, BaseFeatureLayer, StringRef::Empty, StringRef::Empty);

