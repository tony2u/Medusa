// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseGridMovementComponent.h"
#include "Geometry/Grid/GridMap.h"
#include "Node/INode.h"

MEDUSA_BEGIN;



Point2I BaseGridMovementComponent::CurrentIndex() const
{
	INode* node = (INode*)mEntity;
	return mMap->ToIndex(node->Position().To2D());
}

void BaseGridMovementComponent::UpdateDirection(Point2F from, Point2F to)
{
	MoveDirection dir = MoveDirection::None;
	if (mMap->AllowDiagonalMove())
	{
		if (to.X > from.X)
		{
			MEDUSA_FLAG_ADD(dir, MoveDirection::Right);
		}
		else if (to.X < from.X)
		{
			MEDUSA_FLAG_ADD(dir, MoveDirection::Left);
		}

		if (to.Y > from.Y)
		{
			MEDUSA_FLAG_ADD(dir, MoveDirection::Up);
		}
		else if (to.Y < from.Y)
		{
			MEDUSA_FLAG_ADD(dir, MoveDirection::Down);
		}

	}
	else
	{
		float x = Math::Abs(to.X - from.X);
		float y = Math::Abs(to.Y - from.Y);
		if (x>=y)
		{
			//choose x direction
			if (to.X > from.X)
			{
				MEDUSA_FLAG_ADD(dir, MoveDirection::Right);
			}
			else if (to.X < from.X)
			{
				MEDUSA_FLAG_ADD(dir, MoveDirection::Left);
			}
		}
		else
		{
			if (to.Y > from.Y)
			{
				MEDUSA_FLAG_ADD(dir, MoveDirection::Up);
			}
			else if (to.Y < from.Y)
			{
				MEDUSA_FLAG_ADD(dir, MoveDirection::Down);
			}
		}

	}

	if (dir != mDirection)
	{
		OnDirectionChanged(dir);
		mDirection = dir;
	}
}

void BaseGridMovementComponent::OnPositionChanged(const Point3F& oldPos, const Point3F& newPos)
{
	UpdateDirection(oldPos.To2D(), newPos.To2D());
}

MEDUSA_IMPLEMENT_COMPONENT(BaseGridMovementComponent, BaseMovementComponent);
MEDUSA_END;
