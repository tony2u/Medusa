// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTile.h"
#include "TiledImage.h"
#include "TiledObjectLayer.h"
#include "TmxTiledMap.h"
#include "TiledTileset.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"


MEDUSA_BEGIN;

TiledTile::TiledTile(int id/*=0*/)
{
	mId = id;
	mTotalDuration = 0;
	mTerrains.SetAll(-1);
	mProbability = 0.f;
	mImage = nullptr;
	mObjectLayer = nullptr;
}

TiledTile::~TiledTile()
{
	SAFE_DELETE(mImage);
	SAFE_DELETE(mObjectLayer);
}


bool TiledTile::Parse(const pugi::xml_node& node)
{
	//int id = node.attribute("id").as_int(0);
	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		TmxTiledMap::ParseProperties(propertiesNode, MutableProperties());
	}

	StringRef terrainStr = node.attribute("terrain").as_string();
	if (!terrainStr.IsEmpty())
	{
		List<HeapString> strs;
		StringParser::Split(terrainStr, StringRef(","), strs,false);
		mTerrains.LeftTop = (int)strs[0].ToIntWithFailed(-1);
		mTerrains.RightTop = (int)strs[1].ToIntWithFailed(-1);
		mTerrains.LeftBottom = (int)strs[2].ToIntWithFailed(-1);
		mTerrains.RightBottom = (int)strs[3].ToIntWithFailed(-1);
	}

	mProbability = node.attribute("probability").as_float();

	pugi::xml_node imageNode = node.child("image");
	if (!imageNode.empty())
	{
		TiledImage* image = new TiledImage();
		image->Parse(imageNode);
		SetImage(image);
	}

	pugi::xml_node objectGroupNode = node.child("objectgroup");
	if (!objectGroupNode.empty())
	{
		TiledObjectLayer* objectLayer = new TiledObjectLayer();
		objectLayer->Parse(objectGroupNode);
		SetObjectLayer(objectLayer);
	}

	pugi::xml_node animationNode = node.child("animation");
	if (!animationNode.empty())
	{
		FOR_EACH_COLLECTION_STL(i, animationNode.children())
		{
			pugi::xml_node frameNode = *i;
			int tileId = frameNode.attribute("tileid").as_int(0);
			uint durationMilliseconds = frameNode.attribute("duration").as_uint(0);
			AddFrame(tileId, durationMilliseconds);
		}
	}


	const StringRef str2 = "Collision";
	HeapString* collisionStr = mProperties.TryGetByOtherKey(str2, str2.HashCode());
	if (collisionStr != nullptr&&!collisionStr->IsEmpty())
	{
		mCollision = StringParser::StringTo<int>(*collisionStr);
	}


	return true;
}


void TiledTile::SetImage(TiledImage* val)
{
	SAFE_ASSIGN(mImage, val);
}

void TiledTile::SetObjectLayer(TiledObjectLayer* val)
{
	SAFE_ASSIGN(mObjectLayer, val);
}

void TiledTile::AddFrame(int tileId, uint milliseconds)
{
	mFrames.Add(TiledAnimationFrame(tileId, milliseconds));
	mTotalDuration += milliseconds;
}

void TiledTile::TryUpdateRegion(const TiledTileset& tileset)
{
	RETURN_IF_NOT_NULL(mImage);	//is a separate image

	auto* image = tileset.Image();
	RETURN_IF_NULL(image);

	auto* page = image->TexturePage();
	auto* atlas = page->Atlas();
	mRegion = atlas->FindRegion(mId);
}

TextureAtlasPage* TiledTile::Page() const
{
	if (mRegion!=nullptr)
	{
		return mRegion->Page();
	}

	if (mImage!=nullptr)
	{
		return mImage->TexturePage();
	}
	return nullptr;
}

MEDUSA_END;

