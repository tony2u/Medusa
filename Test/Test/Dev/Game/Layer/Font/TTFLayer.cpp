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

	WHeapString str = WHeapString(L"¿ªÊ¼");
	
	auto* label = NodeFactory::Instance().CreateSingleLineLabel(FontId(System::Instance().CurrentFontName(), 88), str);
	//label->SetColor(Color4F(17.f / 255.f, 1.f, 20.f / 255, 1.f));
	AddChild(label);
	label->SetAnchorPoint(AnchorPoint::MiddleBottom);
	label->DockToParent(DockPoint::MiddleCenter);
	return true;
}



MEDUSA_IMPLEMENT_NODE(TTFLayer);

