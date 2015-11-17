// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ShaderFeatureLayer.h"


ShaderFeatureLayer::ShaderFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{

}

ShaderFeatureLayer::~ShaderFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(ShaderFeatureLayer, BaseFeatureLayer, StringRef::Empty);

