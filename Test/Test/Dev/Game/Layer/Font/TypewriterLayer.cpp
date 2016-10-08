// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TypewriterLayer.h"
#include "Node/Action/Effect/TypewriterEffect.h"

TypewriterLayer::TypewriterLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

TypewriterLayer::~TypewriterLayer(void)
{
}

bool TypewriterLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	WHeapString str = WHeapString(L"1234");
	
	auto name=System::Instance().CurrentFontName();
	auto* label = NodeFactory::Instance().CreateMultipleLineLabel(FontId(name, 88), str);
	AddChild(label);
	label->SetAnchorPoint(AnchorPoint::LeftTop);
	label->DockToParent(DockPoint::MiddleCenter);

	TypewriterEffect* effect = new TypewriterEffect(20);
	effect->SetText(L"abcd.efghi.jklmn\naweraew\nawer");
	effect->SetNewLineDelay(2.f);
	effect->SetPeriodDelay(3.f);
	label->RunAction(effect);
	return true;
}



MEDUSA_IMPLEMENT_NODE(TypewriterLayer);

