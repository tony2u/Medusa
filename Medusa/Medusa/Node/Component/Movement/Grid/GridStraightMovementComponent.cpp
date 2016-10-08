// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GridStraightMovementComponent.h"
#include "Node/INode.h"
#include "Geometry/GeometryAlgorithm.h"
#include "Geometry/Navigation/NavigationAlgorithm.h"
#include "Geometry/Grid/GridMap.h"
#include "Core/Math/Random/Random.h"
#include "Core/Action/DelayAction.h"
#include "Core/Collection/Linq.h"

MEDUSA_BEGIN;

GridStraightMovementComponent::GridStraightMovementComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	:BaseGridMovementComponent(name, priority, userData),
	mMoveDurationRange(2.f, 4.f),
	mRestDurationRange(1.f, 2.f)
{
}

bool GridStraightMovementComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IComponent::Update(dt));

	switch (mState)
	{
	case State::None:
		RandNextMovement();
		RandNextDirection(mAllowTurnBack);
		mState = State::Walking;
		PrepareNextStep();
		//continue to waling
	case State::Walking:
		if (mMoveStep > 0)
		{
			if (mMoveGridAction->IsDone())
			{
				--mMoveStep;
				if (mMoveStep > 0)
				{
					//check Obstacle
					if (IsNextStepAvailable())
					{
						//keep current direction
						PrepareNextStep();
						break;
					}
					else
					{
						//turn another direction
						if (!mRestWhenHitObstacle)
						{
							RandNextDirection(false, mForwardDirection);
							PrepareNextStep();
							break;
						}
						else
						{
							RandRest();
							mState = State::Rest;
						}
					}
				}
				else
				{
					RandRest();
					mState = State::Rest;
				}


			}
			else
			{
				break;
			}
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
			RandNextDirection(mAllowTurnBack, mForwardDirection);
			mState = State::Walking;
			PrepareNextStep();
		}
		break;
	default:
		break;
	}


	return true;
}

void GridStraightMovementComponent::RandNextMovement()
{
	float moveDuration = Random::Global().NextFloat(mMoveDurationRange);
	float distance = moveDuration*mVelocity;
	mMoveStep = (uint)Math::Floor(distance / mMap->GridSize());

}

void GridStraightMovementComponent::RandNextDirection(bool allowTurnBack /*= false*/, MoveDirection prevDirection /*= MoveDirection::None*/)
{
	MoveDirection reveseDirection = NavigationAlgorithm::Reverse(prevDirection);
	mForwardVector = Point2I::Zero;
	mForwardDirection = MoveDirection::None;
	INode* node = (INode*)mEntity;
	Point2F curPos = node->Position().To2D();
	Point2I index = mMap->ToIndex(curPos);
	auto* cell = mMap->CellAt(index);
	auto directions = mMap->GetAvailableDirections(*cell, mAgentCapablity, mMap->AllowDiagonalMove());

	uint count = directions.Count();
	if (count > 0)
	{
		//try to find another direction except only prevDirection is available
		if (!allowTurnBack&&reveseDirection != MoveDirection::None)
		{

			directions.RemoveSwap(reveseDirection);
			count = directions.Count();
		}

		if (count > 0)
		{
			mForwardDirection = Linq::RandSelect(directions);
		}
		else
		{
			mForwardDirection = reveseDirection;
		}
	}
	mForwardVector = NavigationAlgorithm::ToVector(mForwardDirection);

}

void GridStraightMovementComponent::PrepareNextStep()
{
	if (mMoveGridAction == nullptr)
	{
		float gridDuration = mMap->GridSize() / mVelocity;
		mMoveGridAction = new MoveToAction(gridDuration);
		mMoveGridAction->KeepAlive();
		RunAction(mMoveGridAction);
		mMoveGridAction->Pause();
	}

	Point3F delta = mForwardVector;
	delta *= mMap->GridSize();
	Point3F dest = Position() + delta;
	mMoveGridAction->SetEndPosition(dest);
	mMoveGridAction->Reset();
	mMoveGridAction->Start();

}

bool GridStraightMovementComponent::IsNextStepAvailable() const
{
	auto index = CurrentIndex();
	auto* cell = mMap->CellAt(index);
	index += mForwardVector;
	return mMap->IsForwardWalkable(*cell, mForwardDirection, mAgentCapablity);
}


void GridStraightMovementComponent::RandRest()
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

MEDUSA_IMPLEMENT_COMPONENT(GridStraightMovementComponent, BaseMovementComponent);
MEDUSA_END;
