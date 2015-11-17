// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "MoveToActionLayer.h"


MoveToActionLayer::MoveToActionLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseActionLayer(name, e)
{
}

MoveToActionLayer::~MoveToActionLayer(void)
{
}


void MoveToActionLayer::RestartSelfAction()
{
	mSprite->StopAllActions();
	mSprite->DockToScreen(DockPoint::LeftCenter);
	Size2F winSize = ResolutionAdapter::Instance().WinSize();
	Point3F destPos = mSprite->Position();
	destPos.X += winSize.Width - mSprite->Width();

	
	MoveToAction* moveTo = new MoveToAction(destPos, 0.3f);
	RateEaseInAction* tweenAction = new RateEaseInAction(moveTo,20.f);
	mSprite->RunAction(tweenAction);
}

MEDUSA_IMPLEMENT_LAYER(MoveToActionLayer, BaseActionLayer, StringRef::Empty);

