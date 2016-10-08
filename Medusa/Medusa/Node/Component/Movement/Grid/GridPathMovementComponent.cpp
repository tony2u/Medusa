// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GridPathMovementComponent.h"
#include "Node/INode.h"
#include "Geometry/GeometryAlgorithm.h"
#include "Geometry/Navigation/NavigationAlgorithm.h"
#include "Geometry/Grid/GridMap.h"

MEDUSA_BEGIN;

GridPathMovementComponent::GridPathMovementComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	:BaseGridMovementComponent(name, priority, userData)
{
	mIsAutoActive = false;
}

bool GridPathMovementComponent::MoveToPixelPosition(Point2F to)
{
	Point2I toIndex = mMap->ToIndex(to);
	return MoveToIndex(toIndex);

}


bool GridPathMovementComponent::MoveToIndex(Point2I toIndex)
{
	INode* node = (INode*)mEntity;
	Point2I fromIndex = mMap->ToIndex(node->Position().To2D());

	Point2I delta = toIndex - fromIndex;
	const GridCell* fromCell = mMap->CellAt(fromIndex);
	const GridCell* toCell = mMap->CellAt(toIndex);

	mPathFinder.SetGraph(mMap);
	mPathFinder.SetOptions(mMap->AllowDiagonalMove());
	mPathFinder.SetAgentCapablity(mAgentCapablity);
	mPath.Clear();

	if (mPathFinder.Run(*fromCell, *toCell, &mPath))
	{
		mStepIndex = 0;
		mPathPoints.Clear();
		for (auto& tnode : mPath)
		{
			mPathPoints.Add(mMap->ToPosition(tnode->Index()));
		}

		Start();
		return true;
	}
	return false;
}

bool GridPathMovementComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IComponent::Update(dt));

	Point2F curPos = Position().To2D();
	Point2F newPos = curPos;
	NavigationAlgorithm::MoveAlongPath(mPathPoints, mStepIndex, newPos, mVelocity*dt);
	SetPosition(newPos);

	if (mStepIndex>= mPathPoints.Count())
	{
		Stop();
	}

	return true;

}


MEDUSA_IMPLEMENT_COMPONENT(GridPathMovementComponent, BaseMovementComponent);
MEDUSA_END;
