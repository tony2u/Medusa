// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "MapFeatureLayer.h"
#include "TiledMapLayer.h"

MapFeatureLayer::MapFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<TiledMapLayer>();
}

MapFeatureLayer::~MapFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_NODE(MapFeatureLayer);

