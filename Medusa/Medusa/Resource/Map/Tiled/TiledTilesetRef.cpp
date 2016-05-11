// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTilesetRef.h"
#include "TiledTileset.h"
#include "TiledTilesetFactory.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"

MEDUSA_BEGIN;
TiledTilesetRef::TiledTilesetRef()
{

}

TiledTilesetRef::~TiledTilesetRef()
{
	SAFE_RELEASE(mTileset);
}

bool TiledTilesetRef::Parse(const pugi::xml_node& node)
{
	// The firstgid and source attribute are kept in the TMX map,
	// since they are map specific.
	mFirstGlobalId = node.attribute("firstgid").as_int(0);

	// If the <tileset> node contains a 'source' tag,
	// the tileset config should be loaded from an external
	// TSX (Tile Set XML) file. That file has the same structure
	// as the <tileset> element in the TMX map.
	const char* sourceName = node.attribute("source").as_string(nullptr);
	if (sourceName != nullptr)
	{
		TiledTileset* tileset = TiledTilesetFactory::Instance().Create(FileIdRef(sourceName));
		SetTileset(tileset);
		return true;
	}

	TiledTileset* tileset = new TiledTileset(FileIdRef(sourceName));
	tileset->Parse(node);
	SetTileset(tileset);
	return true;
}

void TiledTilesetRef::SetTileset(const TiledTileset* val)
{
	SAFE_ASSIGN_REF(mTileset, val);
}


MEDUSA_END;