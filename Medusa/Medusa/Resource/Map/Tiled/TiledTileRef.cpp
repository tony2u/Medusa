// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTileRef.h"

MEDUSA_BEGIN;



TiledTileRef::TiledTileRef() : Tileset(nullptr)
, Id(0)
, GlobalId(0)
, FlippedHorizontally(false)
, FlippedVertically(false)
, FlippedDiagonally(false)
{

}


void TiledTileRef::Initialize(unsigned globalId, int tilesetFirstGlobalId, const TiledTileset* tileset)
{
	Tileset = tileset;
	GlobalId = globalId & ~(FlippedHorizontallyFlag | FlippedVerticallyFlag | FlippedDiagonallyFlag);
	Id = GlobalId - tilesetFirstGlobalId;

	FlippedHorizontally = (globalId & FlippedHorizontallyFlag) != 0;
	FlippedVertically = (globalId & FlippedVerticallyFlag) != 0;
	FlippedDiagonally = (globalId & FlippedDiagonallyFlag) != 0;
}

TiledTileRef::TiledTileRef(unsigned globalId, int tilesetFirstGlobalId, const TiledTileset* tileset)
{
	Initialize(globalId, tilesetFirstGlobalId, tileset);
}


MEDUSA_END;
