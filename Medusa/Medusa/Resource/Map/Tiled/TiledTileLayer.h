// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "ITiledLayer.h"
#include "TiledTileRef.h"

MEDUSA_BEGIN;

class TiledTileLayer : public ITiledLayer
{
public:
	TiledTileLayer();
	~TiledTileLayer();
	virtual TiledLayerType Type()const override { return TiledLayerType::Tile; }

	void InitializeTiles();

	const TiledTileRef& Tile(int x, int y) const { return mTiles[y * mSize.Width + x]; }
	TiledTileRef& MutableTile(int x, int y) { return mTiles[y * mSize.Width + x]; }

	const TiledTileRef& Tile(int index)const { return mTiles[index]; }
	TiledTileRef& MutableTile(int index) { return mTiles[index]; }

private:
	List<TiledTileRef> mTiles;
};

MEDUSA_END;
