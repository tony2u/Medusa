// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "LinearMovementComponent.h"
#include "Node/INode.h"

MEDUSA_BEGIN;

LinearMovementComponent::LinearMovementComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	:BaseMovementComponent(name, priority, userData),
	mMovementLeft(Point2F::Zero)
{

}

MoveDirection LinearMovementComponent::Direction() const
{
	MoveDirection direction = MoveDirection::None;
	if (mMovementLeft.X > 0.f)
	{
		MEDUSA_FLAG_ADD(direction, MoveDirection::Right);
	}
	else if (mMovementLeft.X < 0.f)
	{
		MEDUSA_FLAG_ADD(direction, MoveDirection::Left);
	}

	if (mMovementLeft.Y > 0.f)
	{
		MEDUSA_FLAG_ADD(direction, MoveDirection::Up);
	}
	else if (mMovementLeft.Y < 0.f)
	{
		MEDUSA_FLAG_ADD(direction, MoveDirection::Down);
	}
	return direction;
}

void LinearMovementComponent::OnMovementChanged(Point2F delta)
{
	UpdateK();
}

void LinearMovementComponent::UpdateK()
{
	if (Math::IsZero(mMovementLeft.X))
	{
		mMovementK.X = 0.f;
		mMovementK.Y = 1.f;
	}
	else
	{
		float k = Math::Atan2(mMovementLeft.Y, mMovementLeft.X);
		mMovementK.Y = Math::Sin(k);
		mMovementK.X = Math::Cos(k);
	}

}
void LinearMovementComponent::MoveBy(Point2F delta)
{
	OnMovementChanged(delta);
	Start();
}

void LinearMovementComponent::MoveTo(Point2F to)
{
	INode* node = (INode*)mEntity;
	Point2F delta = to - node->Position().To2D();
	OnMovementChanged(delta);
	Start();
}

bool LinearMovementComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IComponent::Update(dt));

	INode* node = (INode*)mEntity;
	auto delta = mVelocity*dt;	//>0
	Point2F move = delta*mMovementK;

	move.X = Math::Min(Math::Abs(move.X), Math::Abs(mMovementLeft.X))*Math::Sign(mMovementLeft.X);
	move.Y = Math::Min(Math::Abs(move.Y), Math::Abs(mMovementLeft.Y))*Math::Sign(mMovementLeft.Y);

	mMovementLeft -= move;
	node->Move(move);

	if (mMovementLeft.IsNearlyZero())
	{
		Stop();
	}
	return true;
}

MEDUSA_IMPLEMENT_COMPONENT(LinearMovementComponent, BaseMovementComponent);

MEDUSA_END;
