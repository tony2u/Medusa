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

class GridDistanceWanderMovementComponent :public BaseGridMovementComponent
{
	enum class State
	{
		None,
		Walking,
		Checking,
		Rest,
	};
	MEDUSA_DECLARE_COMPONENT(GridDistanceWanderMovementComponent, BaseGridMovementComponent);
public:
	GridDistanceWanderMovementComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	virtual bool Update(float dt)override;
public:
	RangeI MoveDistanceRange() const { return mMoveDistanceRange; }
	void SetMoveDistanceRange(RangeI val) { mMoveDistanceRange = val; }

	RangeF RestDurationRange() const { return mRestDurationRange; }
	void SetRestDurationRange(RangeF val) { mRestDurationRange = val; }
protected:
	void RandNextMovement();
	void RandRest();

protected:
	RangeI mMoveDistanceRange;
	RangeF mRestDurationRange;

	GridPathMovementComponent* mPathMovement = nullptr;
protected:
	State mState = State::None;
private:
	DelayAction* mRestAction = nullptr;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(GridDistanceWanderMovementComponent);
MEDUSA_END;
