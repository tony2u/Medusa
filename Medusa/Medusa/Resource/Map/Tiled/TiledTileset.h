// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Geometry/Point2.h"
#include "Geometry/Size2.h"
#include "Core/Collection/List.h"
#include "TiledTile.h"
#include "TiledTerrain.h"
#include "Resource/IResource.h"
#include "Core/IO/IFileLoadSavable.h"


MEDUSA_BEGIN;

class TiledTileset : public IResource, public IFileLoadSavable
{
public:
	TiledTileset(const FileIdRef& fileId);
	virtual ~TiledTileset();
	virtual ResourceType Type()const override { return ResourceType::Tileset; }

	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = 0)override;
	virtual void Unload()override;

	bool Parse(const pugi::xml_node& node);

	
	Size2U TileSize() const { return mTileSize; }
	void SetTileSize(Size2U val) { mTileSize = val; }

	int Margin() const { return mMargin; }
	void SetMargin(int val) { mMargin = val; }

	int Spacing() const { return mSpacing; }
	void SetSpacing(int val) { mSpacing = val; }

	Point2I TileOffset() const { return mTileOffset; }
	void SetTileOffset(Point2I val) { mTileOffset = val; }

	TiledImage* Image() const { return mImage; }
	void SetImage(TiledImage* val);

	const StringPropertySet& Properties() const { return mProperties; }
	StringPropertySet& MutableProperties() { return mProperties; }
	void SetProperties(const StringPropertySet& val) { mProperties = val; }

	TiledTerrain& NewTerrain();

	void AllocTiles(uint tileCount);
	TiledTile& MutableTileAt(int index);
	const TiledTile& TileAt(int index)const;


private:
	Size2U mTileSize;
	int mMargin;
	int mSpacing;
	Point2I mTileOffset;
	TiledImage* mImage;	//when use collection of images tileset, this field would be null
	
	List< TiledTerrain > mTerrains;
	List< TiledTile > mTiles;
	StringPropertySet mProperties;
	

};

MEDUSA_END;
