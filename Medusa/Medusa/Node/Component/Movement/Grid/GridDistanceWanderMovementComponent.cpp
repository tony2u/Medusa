// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GridDistanceWanderMovementComponent.h"
#include "Node/INode.h"
#include "Geometry/GeometryAlgorithm.h"
#include "Geometry/Navigation/NavigationAlgorithm.h"
#include "Geometry/Grid/GridMap.h"
#include "Core/Math/Random/Random.h"
#include "Core/Action/DelayAction.h"
#include "Core/Collection/Linq.h"
#include "GridPathMovementComponent.h"

MEDUSA_BEGIN;

GridDistanceWanderMovementComponent::GridDistanceWanderMovementComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	:BaseGridMovementComponent(name, priority, userData),
	mMoveDistanceRange(1, 8),
	mRestDurationRange(1.f, 2.f)
{
}

bool GridDistanceWanderMovementComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IComponent::Update(dt));
	if (mPathMovement!=nullptr)
	{
		mPathMovement->Update(dt);
	}
	switch (mState)
	{
	case State::None:
		RandNextMovement();
		mState = State::Walking;
		//continue to waling
	case State::Walking:
		if (mPathMovement->IsRunning())
		{
			break;
		}
		else
		{
			RandRest();
			mState = State::Rest;
		}
		//continue to Rest
	case State::Rest:
		if (mRestAction->IsDone())
		{
			//next movement
			RandNextMovement();
			mState = State::Walking;
		}
		break;
	default:
		break;
	}


	return true;
}

void GridDistanceWanderMovementComponent::RandNextMovement()
{
	//find reachable cells
	int distance = Random::Global().Next(mMoveDistanceRange);
	auto* cell = mMap->CellAt(CurrentIndex());
	List<const GridCell*> outCells;
	mMap->GetReachableCells(*cell, (uint)distance, outCells, mMap->AllowDiagonalMove(), false, mAgentCapablity);
	if (!outCells.IsEmpty())
	{
		const GridCell* targetCell = Linq::RandSelect(outCells);
		if (mPathMovement == nullptr)
		{
			mPathMovement = new GridPathMovementComponent();
			mPathMovement->SetEntity(mEntity);
			mPathMovement->SetMap(mMap);
			mPathMovement->SetAgentCapablity(mAgentCapablity);
			mPathMovement->SetVelocity(mVelocity);

			mPathMovement->OnDirectionChanged += [this](MoveDirection dir)
			{
				//redirect to parent
				OnDirectionChanged(dir);
			};

		}
		mPathMovement->Start();
		mPathMovement->MoveToIndex(targetCell->Index());
	}
}

void GridDistanceWanderMovementComponent::RandRest()
{
	if (mRestAction == nullptr)
	{
		mRestAction = new DelayAction(0.f);
		mRestAction->KeepAlive();
		RunAction(mRestAction);
		mRestAction->Pause();
	}
	float restDuration = Random::Global().NextFloat(mRestDurationRange);
	mRestAction->SetDuration(restDuration);
	mRestAction->Reset();
	mRestAction->Start();

}

MEDUSA_IMPLEMENT_COMPONENT(GridDistanceWanderMovementComponent, BaseMovementComponent);
MEDUSA_END;
