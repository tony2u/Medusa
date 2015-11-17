// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "FontFeatureLayer.h"


FontFeatureLayer::FontFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{

}

FontFeatureLayer::~FontFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(FontFeatureLayer, BaseFeatureLayer, StringRef::Empty);

