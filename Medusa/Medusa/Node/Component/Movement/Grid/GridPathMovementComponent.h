// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseGridMovementComponent.h"
#include "Geometry/GeometryDefines.h"
#include "Core/Pattern/Component/ComponentFactory.h"
#include "Geometry/Grid/GridMap.h"
#include "Geometry/Navigation/AStarPathFinder.h"

MEDUSA_BEGIN;

class GridPathMovementComponent :public BaseGridMovementComponent
{
	MEDUSA_DECLARE_COMPONENT(GridPathMovementComponent, BaseGridMovementComponent);
public:
	GridPathMovementComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	bool MoveToPixelPosition(Point2F to);
	bool MoveToIndex(Point2I toIndex);

	uint PathLength()const { return mPath.Count(); }
	virtual bool Update(float dt)override;
protected:
	void UpdateMoveSteps(Point2F delta);
protected:
	AStarPathFinder<GridMap> mPathFinder;
	List<const GridCell*> mPath;
	List<Point2F> mPathPoints;
	uint mStepIndex=0;

	//TODO:maybe need to re search path if obstacle is changed
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(GridPathMovementComponent);
MEDUSA_END;
