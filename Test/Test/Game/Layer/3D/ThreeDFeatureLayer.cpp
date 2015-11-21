// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ThreeDFeatureLayer.h"
#include "POD3DLayer.h"


ThreeDFeatureLayer::ThreeDFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<POD3DLayer>();

}

ThreeDFeatureLayer::~ThreeDFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(ThreeDFeatureLayer, BaseFeatureLayer, StringRef::Empty);

