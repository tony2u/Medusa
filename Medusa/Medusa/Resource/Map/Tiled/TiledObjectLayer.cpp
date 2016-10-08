// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledObjectLayer.h"
#include "TiledMap.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"

MEDUSA_BEGIN;

TiledObjectLayer::TiledObjectLayer()
	:mColor(Color4B::Black)
{
}



TiledObjectLayer::~TiledObjectLayer()
{

}

bool TiledObjectLayer::Parse(const pugi::xml_node& node)
{
	RETURN_FALSE_IF_FALSE(ITiledLayer::Parse(node));
	const char* colorStr = node.attribute("color").as_string(nullptr);
	mColor = TiledMap::ParseColor(colorStr);

	for (auto objectNode:node.children())
	{
		TiledObject& obj = NewObject();
		obj.Parse(objectNode);
		obj.SetLayer(this);
	}


	return true;
}

MEDUSA_END;
