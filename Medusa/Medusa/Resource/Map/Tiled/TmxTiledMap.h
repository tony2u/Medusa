// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/IO/IFileLoadSavable.h"
#include "Core/IO/IFileLoadSavable.h"
#include "Resource/IResource.h"
#include "TiledDefines.h"
#include "Geometry/Color4.h"
#include "Geometry/Size2.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/Collection/List.h"
#include "TiledTilesetRef.h"
#include "Rendering/RenderingTypes.h"

/*
Features:
custom properties:
InstantiateLayer: the layer class to instantiate 


*/

MEDUSA_BEGIN;

class TmxTiledMap : public IResource, public IFileLoadSavable
{
public:
	TmxTiledMap(const FileIdRef& fileId);
	virtual ~TmxTiledMap();

	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = 0)override;
	virtual void Unload()override;

public:
	float Version() const { return mVersion; }

	static bool ParseProperties(const pugi::xml_node& node, StringPropertySet& outProperties);

	static Color4B ParseColor(const StringRef& str);
	bool Parse(const pugi::xml_node& rootNode);
	virtual ResourceType Type()const override { return ResourceType::Map; }

	const Color4B& BackgroundColor() const { return mBackgroundColor; }
	const Size2U& Size() const { return mSize; }
	const Size2U& TileSize() const { return mTileSize; }

	TiledMapOrientation Orientation() const { return mOrientation; }
	TiledMapRenderOrder RenderOrder() const { return mRenderOrder; }
	TiledMapStaggerAxis StaggerAxis() const { return mStaggerAxis; }
	TiledMapStaggerIndex StaggerIndex() const { return mStaggerIndex; }

	const StringPropertySet& Properties() const { return mProperties; }

	const TiledTilesetRef& GetTileset(int index) const { return mTilesets[index]; }
	const TiledTilesetRef* FindTilesetContainsGlobalId(uint globalId) const;

	const List<ITiledLayer*>& Layers() const { return mLayers; }
	const List<TiledTileLayer*>& TileLayers() const { return mTileLayers; }

	virtual ILayer* Instantiate(const StringRef& className= StringRef::Empty, InstantiateMode mode = InstantiateMode::None)const;

protected:
	Color4B mBackgroundColor;

	TiledMapOrientation mOrientation;
	TiledMapRenderOrder mRenderOrder;
	TiledMapStaggerAxis mStaggerAxis;
	TiledMapStaggerIndex mStaggerIndex;

	Size2U mSize;
	Size2U mTileSize;

	List<ITiledLayer*> mLayers;
	
	List< TiledTileLayer* > mTileLayers;
	List< TiledImageLayer* > mImageLayers;
	List< TiledObjectLayer* > mObjectLayers;

	List< TiledTilesetRef > mTilesets;
	StringPropertySet mProperties;

	float mVersion;
	int mNextObjectId;

	HeapString mInstantiateLayer;
	
};

MEDUSA_END;
