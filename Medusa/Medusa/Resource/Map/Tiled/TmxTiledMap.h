// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "ITiledMap.h"
#include "Core/IO/IFileLoadable.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"


MEDUSA_BEGIN;

class TmxTiledMap : public ITiledMap, public IFileLoadable
{
public:
	TmxTiledMap(const FileIdRef& fileId);
	virtual ~TmxTiledMap();

	virtual bool LoadFromData(StringRef path, const MemoryByteData& data, uint format = 0)override;
	virtual void Unload()override;

public:
	float Version() const { return mVersion; }

	static bool ParseProperties(pugi::xml_node node, StringPropertySet& outProperties);
	static bool ParseTileset(pugi::xml_node node, TiledTileset& outTileset, TmxTiledMap& map);
	static bool ParseTerrain(pugi::xml_node node, TiledTerrain& outTerrain);
	static bool ParseImage(pugi::xml_node node, TiledImage& outImage);
	static bool ParseTile(pugi::xml_node node, TiledTile& outTile, TmxTiledMap& map);
	static bool ParseObject(pugi::xml_node node, TiledObject& outObject);


	static bool ParseLayerBase(pugi::xml_node node, ITiledLayer& outLayer);
	static bool ParseTileLayer(pugi::xml_node node, TiledTileLayer& outLayer, TmxTiledMap& map);
	static bool ParseImageLayer(pugi::xml_node node, TiledImageLayer& outLayer, TmxTiledMap& map);
	static bool ParseObjectLayer(pugi::xml_node node, TiledObjectLayer& outLayer, TmxTiledMap& map);

	static Color4B ParseColor(const StringRef& str);
	bool Parse(pugi::xml_node& rootNode);
private:
	float mVersion;
	int mNextObjectId;

};

MEDUSA_END;
