// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTile.h"
#include "TiledImage.h"
#include "TiledObjectLayer.h"

MEDUSA_BEGIN;

TiledTile::TiledTile(int id)
{
	mTerrains.SetAll(0);
	mProbability = 0.f;
	mImage = nullptr;
	mObjectLayer = nullptr;
}

TiledTile::~TiledTile()
{
	SAFE_DELETE(mImage);
	SAFE_DELETE(mObjectLayer);
}


void TiledTile::SetImage(TiledImage* val)
{
	SAFE_ASSIGN(mImage, val);
}

void TiledTile::SetObjectLayer(TiledObjectLayer* val)
{
	SAFE_ASSIGN(mObjectLayer, val);
}

void TiledTile::AddFrame(int tileId, uint milliseconds)
{
	mFrames.Add(TiledAnimationFrame(tileId, milliseconds));
	mTotalDuration += milliseconds;
}
MEDUSA_END;
