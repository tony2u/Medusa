// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Property/VariantPropertySet.h"
#include "Geometry/Quad.h"
#include "Core/Collection/List.h"
#include "TiledAnimationFrame.h"
#include "Resource/Map/Tiled/TiledImage.h"
#include "Core/Pattern/Share.h"
#include "Geometry/GeometryDefines.h"
/*
Features:
custom properties:
Collision:  a int to indicate collision capability


*/

MEDUSA_BEGIN;
class TiledTile
{
public:
	TiledTile(int id = 0);
	~TiledTile();
	bool operator==(const TiledTile& val)const { return mId == val.mId; }

	bool Parse(const pugi::xml_node& node);

	int Id() const { return mId; }
	void SetId(int val) { mId = val; }

	const VariantPropertySet& Properties() const { return mProperties; }
	VariantPropertySet& MutableProperties() { return mProperties; }
	void SetProperties(const VariantPropertySet& val) { mProperties = val; }


	const Quad<int>& Terrains() const { return mTerrains; }
	Quad<int>& MutableTerrains() { return mTerrains; }
	float Probability() const { return mProbability; }
	void SetProbability(float val) { mProbability = val; }

	TiledImage* Image() const { return mImage; }
	void SetImage(TiledImage* val);

	TiledObjectLayer* ObjectLayer() const { return mObjectLayer; }
	void SetObjectLayer(TiledObjectLayer* val);

	void AddFrame(int tileId, uint milliseconds);

	void TryUpdateRegion(const TiledTileset& tileset);

	TextureAtlasRegion* Region() const { return mRegion; }

	TextureAtlasPage* Page()const;

	int Capability() const { return mCapability; }
	void SetCapability(int val) { mCapability = val; }

	MoveDirection DirectionCapability() const { return mDirectionCapability; }
	void SetDirectionCapability(MoveDirection val) { mDirectionCapability = val; }
	void RemoveDirectionCapability(MoveDirection val) { MEDUSA_FLAG_REMOVE(mDirectionCapability, val); }
	void AddDirectionCapability(MoveDirection val) { MEDUSA_FLAG_ADD(mDirectionCapability, val); }
private:
	int mId;

	VariantPropertySet mProperties;
	Quad<int> mTerrains;
	float mProbability;
	TiledImage* mImage=nullptr;	//if this tile has a separate image
	TiledObjectLayer* mObjectLayer=nullptr;	//used to indicate collision or some else

	uint mTotalDuration;
	List<TiledAnimationFrame> mFrames;

	TextureAtlasRegion* mRegion = nullptr;	//cache for tiled image
	int mCapability = 0;	//default is can pass through
	MoveDirection mDirectionCapability = MoveDirection::All4;	//limit directions to pass into this

};


MEDUSA_END;
