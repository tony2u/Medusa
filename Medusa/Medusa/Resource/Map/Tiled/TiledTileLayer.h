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
	bool Parse(const pugi::xml_node& node);

	void InitializeTiles();

	const List<TiledTileRef>& Tiles() const { return mTiles; }


	const TiledTileRef& Tile(int x, int y) const { return mTiles[y * mSize.Width + x]; }
	TiledTileRef& MutableTile(int x, int y) { return mTiles[y * mSize.Width + x]; }

	const TiledTileRef& Tile(size_t index)const { return mTiles[index]; }
	TiledTileRef& MutableTile(size_t index) { return mTiles[index]; }

	virtual INode* Instantiate(NodeInstantiateInfo* instantiateInfo = nullptr)const override;

protected:
	void AnalyzeTiles();
private:
	List<TiledTileRef> mTiles;
};

MEDUSA_END;
