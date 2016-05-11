// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTerrain.h"
#include "TmxTiledMap.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"

MEDUSA_BEGIN;

TiledTerrain::TiledTerrain()
{
}

TiledTerrain::~TiledTerrain()
{
}

bool TiledTerrain::Parse(const pugi::xml_node& node)
{
	mName= node.attribute("name").as_string(nullptr);
	mTileId = node.attribute("tile").as_int(-1);

	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		TmxTiledMap::ParseProperties(propertiesNode, MutableProperties());
	}

	return true;
}

MEDUSA_END;

