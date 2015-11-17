// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;

struct TiledTileRef
{
	TiledTileRef();
	bool operator<(const TiledTileRef& val)const { return Id < val.Id; }
	bool operator==(const TiledTileRef& val)const { return Id == val.Id; }

	// Will take a gid and read the attributes from the first
	// two bits of it.
	TiledTileRef(unsigned globalId, int tilesetFirstGlobalId, const TiledTileset* tileset);
	void Initialize(unsigned globalId, int tilesetFirstGlobalId, const TiledTileset* tileset);

	const TiledTileset* Tileset;
	uint Id;
	uint GlobalId;

	bool FlippedHorizontally;
	bool FlippedVertically;
	bool FlippedDiagonally;

	const static uint FlippedHorizontallyFlag = 0x80000000;
	const static uint FlippedVerticallyFlag = 0x40000000;
	const static uint FlippedDiagonallyFlag = 0x20000000;
};

MEDUSA_END;