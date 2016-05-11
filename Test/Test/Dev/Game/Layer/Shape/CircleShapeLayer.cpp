// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "CircleShapeLayer.h"


CircleShapeLayer::CircleShapeLayer(StringRef name/*=StringRef::Empty*/, const IEventArg& e/*=IEventArg::Empty*/) :BaseCaseLayer(name, e)
{
}

CircleShapeLayer::~CircleShapeLayer(void)
{
}

bool CircleShapeLayer::Initialize()
{
	RETURN_FALSE_IF_FALSE(BaseCaseLayer::Initialize());

	IShape* shape1= NodeFactory::Instance().CreateCircle(50.f,Math::PI2/720.f,Color4F::Red);
	shape1->SetAnchor(0.5f, 0.5f);
	shape1->SetDock(DockPoint::Percent);
	shape1->SetRelativePosition(mpp(0.3f, 0.5f));
	AddChild(shape1);

	
	return true;
}




MEDUSA_IMPLEMENT_LAYER(CircleShapeLayer, BaseCaseLayer, StringRef::Empty, StringRef::Empty);

