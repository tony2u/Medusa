// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTileset.h"
#include "TiledImage.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "TmxTiledMap.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Core/IO/FileIdRef.h"


MEDUSA_BEGIN;
TiledTileset::TiledTileset(const FileIdRef& fileId)
	: IResource(fileId)
	, mTileSize(Size2U::Zero)
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



bool TiledTileset::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format /*= 0*/)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", fileId, result.description());
		return false;
	}

	pugi::xml_node rootNode = doc.first_child();
	return Parse(rootNode);
}

void TiledTileset::Unload()
{

}

bool TiledTileset::Parse(const pugi::xml_node& node)
{
	mTileSize.Width = node.attribute("tilewidth").as_uint(0);
	mTileSize.Height = node.attribute("tileheight").as_uint(0);

	mMargin= node.attribute("margin").as_int(0);
	mSpacing = node.attribute("spacing").as_int(0);
	//node.attribute("name").as_string(nullptr);	//ignore self name

	Point2I tileOffset = Point2I::Zero;
	pugi::xml_node tileOffsetNode = node.child("tileoffset");
	if (!tileOffsetNode.empty())
	{
		mTileOffset.X = tileOffsetNode.attribute("x").as_int(0);
		mTileOffset.Y = tileOffsetNode.attribute("y").as_int(0);
	}

	pugi::xml_node terrainNode = node.child("terraintypes");
	if (!terrainNode.empty())
	{
		FOR_EACH_COLLECTION_STL(i, terrainNode.children())
		{
			pugi::xml_node child = *i;
			StringRef childName = child.name();
			BREAK_IF_NOT_EQUAL(childName, "terrain");
			TiledTerrain& terrain = NewTerrain();
			terrain.Parse(child);
		}
	}

	pugi::xml_node imageNode = node.child("image");
	if (!imageNode.empty())
	{
		TiledImage* image = new TiledImage();
		image->Parse(imageNode);
		SetImage(image);

		mImage->LoadTiledTexture(mTileSize);
	}


	//add tiles
	uint tileCount = node.attribute("tilecount").as_uint(0);
	if (tileCount == 0)
	{
		tileCount = (Image()->Size().Width / mTileSize.Width) * (Image()->Size().Height / mTileSize.Height);
	}

	AllocTiles(tileCount);

	pugi::xml_node tileNode = node.child("tile");
	while (!tileNode.empty())
	{
		int tileId = tileNode.attribute("id").as_int(0);
		TiledTile& tile = MutableTileAt(tileId);
		tile.Parse(tileNode);
		tileNode = tileNode.next_sibling("tile");
	}


	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		TmxTiledMap::ParseProperties(propertiesNode, MutableProperties());
	}


	FOR_EACH_SIZE(i, tileCount)
	{
		TiledTile& tile = mTiles[i];
		tile.TryUpdateRegion(*this);
	}

	return true;
}

void TiledTileset::SetImage(TiledImage* val)
{
	SAFE_ASSIGN(mImage, val);
}

TiledTerrain& TiledTileset::NewTerrain()
{
	return mTerrains.NewAdd();
}

void TiledTileset::AllocTiles(uint tileCount)
{
	mTiles.ForceReserveCount(tileCount);

	FOR_EACH_SIZE(i, tileCount)
	{
		TiledTile& tile = mTiles[i];
		tile.SetId(i);
	}
}

TiledTile& TiledTileset::MutableTileAt(int index)
{
	return mTiles[index];
}

const TiledTile& TiledTileset::TileAt(int index) const
{
	return mTiles[index];
}

MEDUSA_END;