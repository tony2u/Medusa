// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Size2.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

class TiledTileset
{
public:
	TiledTileset();
	~TiledTileset();

	uint FirstGlobalId() const { return mFirstGlobalId; }
	void SetFirstGlobalId(uint val) { mFirstGlobalId = val; }

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }
	Size2I TileSize() const { return mTileSize; }
	void SetTileSize(Size2I val) { mTileSize = val; }

	int Margin() const { return mMargin; }
	void SetMargin(int val) { mMargin = val; }

	int Spacing() const { return mSpacing; }
	void SetSpacing(int val) { mSpacing = val; }

	Point2I TileOffset() const { return mTileOffset; }
	void SetTileOffset(Point2I val) { mTileOffset = val; }

	const TiledImage* Image() const { return mImage; }
	void SetImage(TiledImage* val);

	const StringPropertySet& Properties() const { return mProperties; }
	StringPropertySet& MutableProperties() { return mProperties; }
	void SetProperties(const StringPropertySet& val) { mProperties = val; }

	void AddTerrain(TiledTerrain* item);
	void AddTile(TiledTile* item);

	TiledTile* MutableTileWithIndex(int index)const;

private:
	uint mFirstGlobalId;
	HeapString mName;
	Size2I mTileSize;
	int mMargin;
	int mSpacing;
	Point2I mTileOffset;
	TiledImage* mImage;
	
	List< TiledTerrain* > mTerrains;
	List< TiledTile* > mTiles;
	StringPropertySet mProperties;
	
};

MEDUSA_END;
