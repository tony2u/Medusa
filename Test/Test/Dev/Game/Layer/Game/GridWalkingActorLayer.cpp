// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "GridWalkingActorLayer.h"
#include "Game/Actor/GridWalkingActor.h"
#include "Node/Component/Movement/Grid/GridPathMovementComponent.h"
#include "Geometry/Navigation/NavigationAlgorithm.h"


GridWalkingActorLayer::GridWalkingActorLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

GridWalkingActorLayer::~GridWalkingActorLayer(void)
{
}

bool GridWalkingActorLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	float cellSize = 64.f;
	auto winSize = ResolutionAdapter::Instance().WinSize();

	mMap.Alloc(winSize,cellSize);

	auto lineShape = NodeFactory::Instance().CreateLine(Point3F::Zero, mppp(winSize.Width, 0.f, 0.f), Color4F::Green);

	FOR_EACH_SIZE(i, mMap.Width())
	{
		lineShape->AddLine(mppp(i*cellSize, 0.f, 0.f), mppp(i*cellSize, winSize.Height, 0.f));
	}

	FOR_EACH_SIZE(i, mMap.Height())
	{
		lineShape->AddLine(mppp(0.f, i*cellSize, 0.f), mppp(winSize.Width, i*cellSize, 0.f));
	}

	AddChild(lineShape);

	GridWalkingActor* actor = new GridWalkingActor("Actor");
	actor->SetMap(&mMap);

	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture("Hearts.png");
	actor->Initialize();
	actor->SetRenderingObject(renderingObject);
	//actor->SetAnchorPoint(AnchorPoint::MiddleCenter);
	AddChild(actor);
	//actor->DockToParent(DockPoint::MiddleCenter);
	/*auto moveComponent = actor->FindComponent<GridPathMovementComponent>();
	moveComponent->SetVelocity(200.f);*/

	/*MutableInput().AddTapGestureHandler([this, actor, cellSize](INode* sender, TapGestureEventArg& e)
	{
		auto gridIndex = NavigationAlgorithm::ToGridIndex(cellSize, e.TouchInfo.Pos);

		auto moveComponent = actor->FindComponent<GridPathMovementComponent>();
		moveComponent->MoveToPixelPosition(e.TouchInfo.Pos);
	}
	);*/

	auto animatorComponent = actor->FindComponent<AnimatorComponent>();
	ITimeline* up = TimelineFactory::Instance().CreateRenderingObjectTimelineFromSingleTexture("Up", "StudentWalking.png", 4, 4, 0, 3, 4.f, true);
	ITimeline* right = TimelineFactory::Instance().CreateRenderingObjectTimelineFromSingleTexture("Right", "StudentWalking.png", 4, 4, 4, 7, 4.f, true);
	ITimeline* left = TimelineFactory::Instance().CreateRenderingObjectTimelineFromSingleTexture("Left", "StudentWalking.png", 4, 4, 8, 11, 4.f, true);
	ITimeline* down = TimelineFactory::Instance().CreateRenderingObjectTimelineFromSingleTexture("Down", "StudentWalking.png", 4, 4, 12, 15, 4.f, true);
	animatorComponent->Add(down);
	animatorComponent->Add(left);
	animatorComponent->Add(right);
	animatorComponent->Add(up);
	animatorComponent->SetDefaultAnimation("Right");

	return true;
}




MEDUSA_IMPLEMENT_NODE(GridWalkingActorLayer);

