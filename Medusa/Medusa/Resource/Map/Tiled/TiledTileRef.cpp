// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTileRef.h"
#include "TiledTilesetRef.h"
#include "TiledTileset.h"
#include "TiledTile.h"
#include "Node/NodeFactory.h"
#include "Node/Sprite/Sprite.h"
#include "TiledImage.h"
#include "Rendering/RenderingObjectFactory.h"
#include "TiledMapInstantiateInfo.h"

MEDUSA_BEGIN;



TiledTileRef::TiledTileRef()
	: mTile(nullptr),
	mTileGlobalId(0),
	mPosition(Point2I::Zero)
{

}


void TiledTileRef::Initialize(const Point2I& position, uint globalId, const TiledTilesetRef* tilesetRef)
{
	mPosition = position;
	mTileGlobalId = globalId;
	RETURN_IF_NULL(tilesetRef);

	uint pureGlobalId = globalId & ~(FlippedHorizontallyFlag | FlippedVerticallyFlag | FlippedDiagonallyFlag);
	uint id = pureGlobalId - tilesetRef->FirstGlobalId();

	const auto& tileset = tilesetRef->Tileset();
	const TiledTile& tile = tileset->TileAt(id);
	mTile = &tile;
}


uint TiledTileRef::TileId() const
{
	return mTile->Id();
}

int TiledTileRef::Capability() const
{
	return mTile->Capability();
}

MoveDirection TiledTileRef::DirectionCapability() const
{
	return mTile->DirectionCapability();
}

INode* TiledTileRef::Instantiate(NodeInstantiateInfo* instantiateInfo /*= nullptr*/) const
{
	RETURN_NULL_IF_NULL(mTile);

	TiledMapInstantiateInfo* mapInstantiateInfo = (TiledMapInstantiateInfo*)instantiateInfo;

	INode* node = nullptr;
	const auto* image = mTile->Image();
	if (mapInstantiateInfo != nullptr&&mapInstantiateInfo->OnTileRefInstantiate!=nullptr)
	{
		if (image != nullptr)
		{
			//has separate image
			auto texture = image->LoadSeparateTexture();
			auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture(texture);
			node = mapInstantiateInfo->OnTileRefInstantiate(*this, renderingObject, mapInstantiateInfo);
		}
		else if (mTile->Region() != nullptr)
		{
			auto renderingObject = RenderingObjectFactory::Instance().CreateFromTextureAtlasRegion(mTile->Region());
			node = mapInstantiateInfo->OnTileRefInstantiate(*this, renderingObject, mapInstantiateInfo);
		}
	}
	else
	{
		if (image != nullptr)
		{
			//has separate image
			auto texture = image->LoadSeparateTexture();
			node = NodeFactory::Instance().CreateSprite(texture);
		}
		else if (mTile->Region() != nullptr)
		{
			node = NodeFactory::Instance().CreateSpriteFromAtlasRegion(mTile->Region());
		}
	}

	if (node != nullptr)
	{
		node->SetUserData((void*)mTile);
	}

	return node;
}

MEDUSA_END;

