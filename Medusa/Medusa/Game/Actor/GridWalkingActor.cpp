// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GridWalkingActor.h"
#include "Node/NodeFactory.h"
#include "Node/Component/Movement/Grid/GridPathMovementComponent.h"
#include "Node/Component/Movement/Grid/GridDistanceWanderMovementComponent.h"

#include "Node/Component/AnimatorComponent.h"

MEDUSA_BEGIN;

GridWalkingActor::GridWalkingActor(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:INode(name,e)
{

}

GridWalkingActor::~GridWalkingActor( void )
{

}

bool GridWalkingActor::Initialize()
{
	mPathMovementComponent = AddComponent<GridPathMovementComponent>();
	mPathMovementComponent->SetMap(mMap);
	mPathMovementComponent->SetAgentCapablity(0);

	mWanderMovementComponent = AddComponent<GridDistanceWanderMovementComponent>();
	mWanderMovementComponent->SetMap(mMap);
	mWanderMovementComponent->SetAgentCapablity(0);
	mWanderMovementComponent->SetVelocity(80.f);

	mAnimator = AddComponent<AnimatorComponent>();
	mAnimator->Start();

	mPathMovementComponent->OnDirectionChanged += [this](MoveDirection dir)
	{
		switch (dir)
		{
		case MoveDirection::Left:
			mAnimator->SwitchTo("Left");
			break;
		case MoveDirection::Right:
			mAnimator->SwitchTo("Right");
			break;
		case MoveDirection::Down:
			mAnimator->SwitchTo("Down");
			break;
		case MoveDirection::Up:
			mAnimator->SwitchTo("Up");
			break;
		default:
			break;
		}
	};

	mPathMovementComponent->OnStart += [this] 
	{
		mAnimator->ResumeAnimation();
	};

	mPathMovementComponent->OnStop += [this]
	{
		mAnimator->PauseAnimation();
	};

	
	mWanderMovementComponent->OnDirectionChanged += [this](MoveDirection dir)
	{
		switch (dir)
		{
		case MoveDirection::Left:
			mAnimator->SwitchTo("Left");
			break;
		case MoveDirection::Right:
			mAnimator->SwitchTo("Right");
			break;
		case MoveDirection::Down:
			mAnimator->SwitchTo("Down");
			break;
		case MoveDirection::Up:
			mAnimator->SwitchTo("Up");
			break;
		default:
			break;
		}
	};

	mPathMovementComponent->EnableAutoActive(false);
	mPathMovementComponent->Pause();
	return true;
}

void GridWalkingActor::SetAgentCapablity(uint val)
{
	mPathMovementComponent->SetAgentCapablity(val);
	mWanderMovementComponent->SetAgentCapablity(val);

	
}

uint GridWalkingActor::AgentCapablity() const
{
	return mPathMovementComponent->AgentCapablity();
}

MEDUSA_IMPLEMENT_NODE(GridWalkingActor);
MEDUSA_END;
