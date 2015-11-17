// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "ProgressBarLayer.h"


ProgressBarLayer::ProgressBarLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{



}

ProgressBarLayer::~ProgressBarLayer(void)
{
}

bool ProgressBarLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	TextureProgressBar* node=NodeFactory::Instance().CreateTextureProgressBar(ProgressType::HorizontalLeftToRight,"HpOwn.png","HpBox.png",0.f);
	node->SetDock(DockPoint::MiddleCenter);
	node->SetAnchor(0.5f,0.5f);
	AddChild(node);


	ProgressByAction* progrssBy1 = new ProgressByAction(1.f, 1.f);
	ProgressByAction* progrssBy2 = new ProgressByAction(-1.f, 1.f);
	SequenceAction* seq = new SequenceAction(progrssBy1, progrssBy2);
	RepeatedForeverAction* req = new RepeatedForeverAction(seq);
	node->RunAction(req);

	return true;
}




MEDUSA_IMPLEMENT_LAYER(ProgressBarLayer, BaseCaseLayer, StringRef::Empty);

