// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "RectangleShapeLayer.h"


RectangleShapeLayer::RectangleShapeLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

RectangleShapeLayer::~RectangleShapeLayer(void)
{
}

bool RectangleShapeLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	IShape* rectShape= NodeFactory::Instance().CreateRect(msize(100, 100), Color4F::Red);
	rectShape->SetDock(DockPoint::MiddleCenter);
	rectShape->SetAnchor(0.5f, 0.5f);
	AddChild(rectShape);


	return true;
}




MEDUSA_IMPLEMENT_LAYER(RectangleShapeLayer, BaseCaseLayer, StringRef::Empty);

