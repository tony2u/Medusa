// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ITiledLayer.h"

MEDUSA_BEGIN;

ITiledLayer::ITiledLayer()
	: mPosition(Point2I::Zero),
	mSize(Size2I::Zero),
	mOpacity(1.f),
	mIsVisible(true),
	mZOrder(0)
{
	
}

ITiledLayer::~ITiledLayer()
{
}

MEDUSA_END;