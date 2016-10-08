// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"
#include "Geometry/Grid/GridMap.h"
#include "Geometry/Navigation/AStarPathFinder.h"
#include "Geometry/Grid/GridCell.h"

class GridWalkingActorLayer :public BaseCaseLayer
{
	MEDUSA_NODE(GridWalkingActorLayer, BaseCaseLayer);
	using MapType = GridMap;
public:
	GridWalkingActorLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~GridWalkingActorLayer(void);
	virtual bool Initialize()override;

private:
	MapType mMap;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(GridWalkingActorLayer);
