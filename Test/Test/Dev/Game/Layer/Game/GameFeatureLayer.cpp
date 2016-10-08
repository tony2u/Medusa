// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "GameFeatureLayer.h"
#include "GridWalkingActorLayer.h"

GameFeatureLayer::GameFeatureLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseFeatureLayer(name, e)
{
	Register<GridWalkingActorLayer>();
}

GameFeatureLayer::~GameFeatureLayer(void)
{
}


MEDUSA_IMPLEMENT_NODE(GameFeatureLayer);

