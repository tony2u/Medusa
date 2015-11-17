// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ITiledMap.h"
#include "ITiledLayer.h"
#include "TiledTileset.h"
#include "TiledTileRef.h"

MEDUSA_BEGIN;


ITiledMap::ITiledMap(const FileIdRef& fileId)
	:IResource(fileId),
	mBackgroundColor(Color4B::Black),
	mOrientation(TiledMapOrientation::Orthogonal),
	mRenderOrder(TiledMapRenderOrder::RightDown),
	mStaggerAxis(TiledMapStaggerAxis::None),
	mStaggerIndex(TiledMapStaggerIndex::None),
	mSize(Size2I::Zero),
	mTileSize(Size2I::Zero)
{
}

ITiledMap::~ITiledMap()
{
	SAFE_DELETE_COLLECTION(mLayers);
	mTileLayers.Clear();
	mObjectLayers.Clear();
	mImageLayers.Clear();

	SAFE_DELETE_COLLECTION(mTilesets);
}



const TiledTileset* ITiledMap::FindTilesetContainsGlobalId(uint globalId) const
{
	// Clean up the flags from the globalId 
	globalId &= ~(TiledTileRef::FlippedHorizontallyFlag | TiledTileRef::FlippedVerticallyFlag | TiledTileRef::FlippedDiagonallyFlag);

	intp count = mTilesets.Count();
	FOR_EACH_INT_END_BEGIN(i,count - 1, 0)
	{
		// If the gid beyond the tileset global id return it.
		if (globalId >= mTilesets[i]->FirstGlobalId())
		{
			return mTilesets[i];
		}
	}

	return nullptr;
}

MEDUSA_END;