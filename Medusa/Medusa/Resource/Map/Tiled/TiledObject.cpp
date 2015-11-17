// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledObject.h"
#include "Core/Geometry/Ellipse.h"
#include "Core/Geometry/Polygon.h"

MEDUSA_BEGIN;
TiledObject::TiledObject()
	:mPosition(Point2I::Zero),
	mSize(Size2I::Zero),
	mIsVisible(true),
	mRotation(0.f),
	mTile(nullptr),
	mEllipse(nullptr),
	mPolygon(nullptr),
	mPolyline(nullptr)
{
}

TiledObject::~TiledObject()
{
	SAFE_DELETE(mEllipse);
	SAFE_DELETE(mPolygon);
	SAFE_DELETE(mPolyline);
}
MEDUSA_END;
