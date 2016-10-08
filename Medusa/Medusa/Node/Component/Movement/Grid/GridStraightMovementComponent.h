// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseGridMovementComponent.h"
#include "Geometry/GeometryDefines.h"
#include "Core/Pattern/Component/ComponentFactory.h"
#include "Geometry/Grid/GridMap.h"
#include "Geometry/Navigation/AStarPathFinder.h"
#include "Core/Math/Range.h"

MEDUSA_BEGIN;

class GridStraightMovementComponent :public BaseGridMovementComponent
{
	enum class State
	{
		None,
		Walking,
		Checking,
		Rest,
	};
	MEDUSA_DECLARE_COMPONENT(GridStraightMovementComponent, BaseGridMovementComponent);
public:
	GridStraightMovementComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	virtual bool Update(float dt)override;
public:
	RangeF MoveDurationRange() const { return mMoveDurationRange; }
	void SetMoveDurationRange(RangeF val) { mMoveDurationRange = val; }

	RangeF RestDurationRange() const { return mRestDurationRange; }
	void SetRestDurationRange(RangeF val) { mRestDurationRange = val; }

	bool AllowTurnBack() const { return mAllowTurnBack; }
	void EnableAllowTurnBack(bool val) { mAllowTurnBack = val; }

	bool RestWhenHitObstacle() const { return mRestWhenHitObstacle; }
	void EnableRestWhenHitObstacle(bool val) { mRestWhenHitObstacle = val; }
protected:
	void RandNextMovement();
	void RandNextDirection(bool allowTurnBack = false,MoveDirection prevDirection=MoveDirection::None);
	void PrepareNextStep();
	bool IsNextStepAvailable()const;

	void RandRest();

protected:
	RangeF mMoveDurationRange;
	RangeF mRestDurationRange;
	
	bool mAllowTurnBack = false;	//allow to turn back over
	bool mRestWhenHitObstacle = false;
protected:
	uint mMoveStep=0;
	Point2I mForwardVector;
	MoveDirection mForwardDirection= MoveDirection::None;
	State mState=State::None;
private:
	MoveToAction* mMoveGridAction=nullptr;
	DelayAction* mRestAction = nullptr;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(GridStraightMovementComponent);
MEDUSA_END;
