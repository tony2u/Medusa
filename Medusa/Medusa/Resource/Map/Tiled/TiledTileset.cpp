// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTileset.h"
#include "TiledImage.h"

MEDUSA_BEGIN;
TiledTileset::TiledTileset()
	: mFirstGlobalId(0)
	, mTileSize(Size2I::Zero)
	, mMargin(0)
	, mSpacing(0)
	, mImage(nullptr)
	, mTiles()
{
}

TiledTileset::~TiledTileset()
{
	SAFE_DELETE(mImage);
}

void TiledTileset::SetImage(TiledImage* val)
{
	SAFE_ASSIGN(mImage, val);
}

void TiledTileset::AddTerrain(TiledTerrain* item)
{
	mTerrains.Add(item);
}


void TiledTileset::AddTile(TiledTile* item)
{
	mTiles.Add(item);
}

TiledTile* TiledTileset::MutableTileWithIndex(int index) const
{
	return mTiles[index];
}

MEDUSA_END;