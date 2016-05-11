// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TTFLayer.h"


TTFLayer::TTFLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

TTFLayer::~TTFLayer(void)
{
}

bool TTFLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	auto* label = NodeFactory::Instance().CreateSingleLineLabel(FontId("arial.ttf", 88), "The quick brown fox");
	//label->SetColor(Color4F(17.f / 255.f, 1.f, 20.f / 255, 1.f));
	AddChild(label);
	label->SetAnchorPoint(AnchorPoint::MiddleBottom);
	label->DockToParent(DockPoint::MiddleCenter);
	return true;
}



MEDUSA_IMPLEMENT_LAYER(TTFLayer, BaseCaseLayer, StringRef::Empty, StringRef::Empty);

