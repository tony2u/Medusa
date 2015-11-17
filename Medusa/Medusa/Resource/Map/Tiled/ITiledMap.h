// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/IO/IFileLoadable.h"
#include "Resource/IResource.h"
#include "TiledDefines.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Size2.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

class ITiledMap : public IResource
{
public:
	ITiledMap(const FileIdRef& fileId);
	virtual ~ITiledMap();
	virtual ResourceType Type()const override { return ResourceType::Map; }


	const Color4B& BackgroundColor() const { return mBackgroundColor; }
	const Size2I& Size() const { return mSize; }
	TiledMapOrientation Orientation() const { return mOrientation; }
	TiledMapRenderOrder RenderOrder() const { return mRenderOrder; }
	TiledMapStaggerAxis StaggerAxis() const { return mStaggerAxis; }
	TiledMapStaggerIndex StaggerIndex() const { return mStaggerIndex; }

	const StringPropertySet& Properties() const { return mProperties; }

	const TiledTileset *GetTileset(int index) const { return mTilesets[index]; }
	const TiledTileset* FindTilesetContainsGlobalId(uint globalId) const;

protected:
	Color4B mBackgroundColor;

	TiledMapOrientation mOrientation;
	TiledMapRenderOrder mRenderOrder;
	TiledMapStaggerAxis mStaggerAxis;
	TiledMapStaggerIndex mStaggerIndex;

	Size2I mSize;
	Size2I mTileSize;


	List<ITiledLayer*> mLayers;
	List< TiledTileLayer* > mTileLayers;
	List< TiledImageLayer* > mImageLayers;
	List< TiledObjectLayer* > mObjectLayers;
	List< TiledTileset* > mTilesets;
	StringPropertySet mProperties;
};

MEDUSA_END;
