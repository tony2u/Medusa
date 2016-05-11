// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ScrollComponentLayer.h"


ScrollComponentLayer::ScrollComponentLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

ScrollComponentLayer::~ScrollComponentLayer(void)
{
}

bool ScrollComponentLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());


	NormalLayer* normalLayer = new NormalLayer();
	float winWidth = ResolutionAdapter::Instance().WinWidth();
	float winHeight = ResolutionAdapter::Instance().WinHeight();

	FOR_EACH_UINT32(i, mChildCount)
	{
		Sprite* child = NodeFactory::Instance().CreateSprite(FileIdRef("Background.png", i));
		child->SetPositionX(winWidth*i);
		normalLayer->AddChild(child);
	}

	mComponent = ComponentFactory::Instance().Create<ScrollComponent>();
	mComponent->Initialize(Rect2F(Point2F::Zero, Size2F(winWidth*mChildCount, winHeight)), ResolutionAdapter::Instance().WinRect(), ScrollDirection::HorizontalFromLeft, true);

	AddChild(normalLayer);
	normalLayer->AddComponent(mComponent);

	/*ScrollComponentScrollByPageAction* moveby = new ScrollComponentScrollByPageAction(mpp(4.f, 0.f), 4.f);
	ScrollComponentScrollByPageAction* moveback = moveby->Reverse();
	SequenceAction* seq = new SequenceAction(moveby, moveback);
	RepeatedForeverAction* rep = new RepeatedForeverAction(seq);*/

	//mComponent->RunAction(rep);
	return true;
}

void ScrollComponentLayer::OnRestart()
{



}

MEDUSA_IMPLEMENT_LAYER(ScrollComponentLayer, BaseCaseLayer, StringRef::Empty, StringRef::Empty);

