// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTileLayer.h"

MEDUSA_BEGIN;
TiledTileLayer::TiledTileLayer()
{
}

TiledTileLayer::~TiledTileLayer()
{
}

void TiledTileLayer::InitializeTiles()
{
	mTiles.ForceReserveCount(mSize.Area());
}

MEDUSA_END;