// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "BaseActionLayer.h"


BaseActionLayer::BaseActionLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

BaseActionLayer::~BaseActionLayer(void)
{
}

bool BaseActionLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	mSprite = NodeFactory::Instance().CreateSprite("test2.png");
	mSprite->DockToScreen(DockPoint::LeftCenter);
	AddChild(mSprite);

	RestartSelfAction();
	return true;
}

void BaseActionLayer::OnRestart()
{
	RestartSelfAction();
}


MEDUSA_IMPLEMENT_NODE(BaseActionLayer);

