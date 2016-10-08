// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ParallaxComponentLayer.h"


ParallaxComponentLayer::ParallaxComponentLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

ParallaxComponentLayer::~ParallaxComponentLayer(void)
{
}

bool ParallaxComponentLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	mMainSprite = NodeFactory::Instance().CreateSprite("test2.png");
	mMainSprite->DockToScreen(DockPoint::MiddleTop);
	mMainSprite->SetAnchorPoint(AnchorPoint::MiddleTop);
	AddChild(mMainSprite);

	mComponent = ComponentFactory::Instance().Create<ParallaxComponent>();
	mMainSprite->AddComponent(mComponent);

	
	FOR_EACH_SIZE(i, mChildCount)
	{
		Sprite* child = NodeFactory::Instance().CreateSprite("test2.png");
		child->SetAnchorPoint(AnchorPoint::MiddleTop);
		child->SetPosition(mMainSprite->Position());
		child->MoveY(-child->Height()*(i+1));
		AddChild(child);
		Point3F ratio = Point3F::One;
		ratio.X = (float)(i + 1) / mChildCount;

		mComponent->EnableParallax(child, ratio, child->Position());
	}
	
	ParallaxComponentMoveByAction* moveby = new ParallaxComponentMoveByAction(mppp(mChildCount*mMainSprite->Width(), 0.f, 0.f), 2.f);
	ParallaxComponentMoveByAction* moveback = moveby->Reverse();
	SequenceAction* seq = new SequenceAction(moveby, moveback);
	RepeatedForeverAction* rep = new RepeatedForeverAction(seq);

	mComponent->RunAction(rep);


	return true;
}

void ParallaxComponentLayer::OnRestart()
{
	mComponent->RestartAllActions();

	

}

MEDUSA_IMPLEMENT_NODE(ParallaxComponentLayer);

