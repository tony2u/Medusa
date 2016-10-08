// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TiledMapLayer.h"
#include "Resource/Map/Tiled/TiledMapInstantiateInfo.h"

TiledMapLayer::TiledMapLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

TiledMapLayer::~TiledMapLayer(void)
{
}

bool TiledMapLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());
	auto tiledMap = TiledMapFactory::Instance().Create(mf("Room.tmx", 1));
	mMap.Expand(tiledMap->Size() * 4);
	mMap.SetGridSize((float)tiledMap->TileSize().Width);

	TiledMapInstantiateInfo info;
	info.OnTileRefInstantiate = [this](const TiledTileRef& tiledRef, const RenderingObject& renderingObject, TiledMapInstantiateInfo* instantiateInfo)->INode*
	{
		Point2I pos = tiledRef.Position();
		if (instantiateInfo != nullptr)
		{
			pos += instantiateInfo->Offset;
		}

		GridCell* cell = mMap.TryAddCell(pos);
		cell->AddCapability(tiledRef.Capability());
		cell->OverlapDirectionCapability(tiledRef.DirectionCapability());

		TiledTileLayer* layer = tiledRef.Layer();
		if (layer->Name()=="Role")
		{
			cell->SetCapability(1);
		}

		return NodeFactory::Instance().CreateSprite(renderingObject);
	};
	info.ParentNode = this;

	tiledMap->Instantiate(&info);

	info.Offset = Point2I(tiledMap->Width(), 0);
	tiledMap->Instantiate(&info);

	info.Offset = Point2I(0, tiledMap->Height());
	tiledMap->Instantiate(&info);

	info.Offset = Point2I(tiledMap->Width(), tiledMap->Height());
	tiledMap->Instantiate(&info);
	//////////////////////////////////////////////////////////////////////////
	GridWalkingActor* actor = new GridWalkingActor("Actor");
	actor->SetMap(&mMap);
	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture("Hearts.png");
	actor->Initialize();
	actor->SetAgentCapablity(0);
	actor->SetRenderingObject(renderingObject);
	//actor->SetAnchorPoint(AnchorPoint::MiddleCenter);
	AddChild(actor);
	//actor->DockToParent(DockPoint::MiddleCenter);
	auto moveComponent = actor->FindComponent<GridPathMovementComponent>();
	moveComponent->SetVelocity(200.f);

	MutableInput().AddTapGestureHandler([this, actor](INode* sender, TapGestureEventArg& e)
	{
		auto gridIndex = mMap.ToIndex(e.TouchInfo.Pos);

		auto moveComponent = actor->FindComponent<GridPathMovementComponent>();
		moveComponent->MoveToPixelPosition(e.TouchInfo.Pos);
	}
	);

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




MEDUSA_IMPLEMENT_NODE(TiledMapLayer);

