// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "PerformanceFeatureLayer.h"


PerformanceFeatureLayer::PerformanceFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{

}

PerformanceFeatureLayer::~PerformanceFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_LAYER(PerformanceFeatureLayer, BaseFeatureLayer, StringRef::Empty, StringRef::Empty);

