// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ParallaxScrollComponentLayer.h"


ParallaxScrollComponentLayer::ParallaxScrollComponentLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

ParallaxScrollComponentLayer::~ParallaxScrollComponentLayer(void)
{
}

bool ParallaxScrollComponentLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());


	NormalLayer* normalLayer = new NormalLayer();
	float winWidth = ResolutionAdapter::Instance().WinWidth();
	float winHeight = ResolutionAdapter::Instance().WinHeight();

	//back ground
	FOR_EACH_UINT32(i, mChildCount)
	{
		Sprite* child = NodeFactory::Instance().CreateSprite(FileIdRef("Background.jpg", i));
		child->SetPositionX(winWidth*i);
		normalLayer->AddChild(child);
	}
	//foreground
	mComponent = ComponentFactory::Instance().Create<ParallaxScrollComponent>();
	mComponent->Initialize(Rect2F(Point2F::Zero, Size2F(winWidth*mChildCount, winHeight)), ResolutionAdapter::Instance().WinRect(), ScrollDirection::HorizontalFromLeft, true);

	Sprite* mainSprite = NodeFactory::Instance().CreateSprite("test2.png");
	mainSprite->DockToScreen(DockPoint::MiddleTop);
	mainSprite->SetAnchorPoint(AnchorPoint::MiddleTop);
	normalLayer->AddChild(mainSprite);

	FOR_EACH_SIZE(i, mChildCount)
	{
		Sprite* child = NodeFactory::Instance().CreateSprite("test2.png");
		child->SetAnchorPoint(AnchorPoint::MiddleTop);
		child->SetPosition(mainSprite->Position());
		child->MoveY(-child->Height()*(i + 1));
		normalLayer->AddChild(child);
		Point3F ratio = Point3F::One;
		ratio.X = (float)(mChildCount-i) / mChildCount;

		mComponent->EnableParallax(child, ratio, child->Position());
	}

	

	AddChild(normalLayer);
	normalLayer->AddComponent(mComponent);

	ScrollComponentScrollByPageAction* moveby = new ScrollComponentScrollByPageAction(mpp(4.f, 0.f), 4.f);
	ScrollComponentScrollByPageAction* moveback = moveby->Reverse();
	SequenceAction* seq = new SequenceAction(moveby, moveback);
	RepeatedForeverAction* rep = new RepeatedForeverAction(seq);

	mComponent->RunAction(rep);

	MutableInput().AddIMEHandler(nullptr, Bind(&ParallaxScrollComponentLayer::OnKeyDown,this), nullptr);
	return true;
}

void ParallaxScrollComponentLayer::OnRestart()
{



}

void ParallaxScrollComponentLayer::OnKeyDown(INode* sender, KeyDownEventArg& e)
{
	if (e.KeyCode() == Keys::Left)
	{
		mComponent->ScrollModel()->ScrollBy(mpp(-10.f, 0.f));
	}
	else if (e.KeyCode() == Keys::Right)
	{
		mComponent->ScrollModel()->ScrollBy(mpp(10.f, 0.f));
	}
}

MEDUSA_IMPLEMENT_NODE(ParallaxScrollComponentLayer);

