// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/Geometry/Quad.h"
#include "Core/Collection/List.h"
#include "TiledAnimationFrame.h"

MEDUSA_BEGIN;
class TiledTile
{
public:
	TiledTile(int id);
	TiledTile();
	~TiledTile();

	const StringPropertySet& Properties() const { return mProperties; }
	StringPropertySet& MutableProperties() { return mProperties; }
	void SetProperties(const StringPropertySet& val) { mProperties = val; }


	const Quad<int>& Terrains() const { return mTerrains; }
	Quad<int>& MutableTerrains()  { return mTerrains; }
	float Probability() const { return mProbability; }
	void SetProbability(float val) { mProbability = val; }

	TiledImage* Image() const { return mImage; }
	void SetImage(TiledImage* val);

	TiledObjectLayer* ObjectLayer() const { return mObjectLayer; }
	void SetObjectLayer(TiledObjectLayer* val);

	void AddFrame(int tileId, uint milliseconds);
private:
	int mId;
	StringPropertySet mProperties;
	Quad<int> mTerrains;
	float mProbability;
	TiledImage* mImage;	//if this tile has a separate image
	TiledObjectLayer* mObjectLayer;	//used to indicate collision or some else
	
	uint mTotalDuration;
	List<TiledAnimationFrame> mFrames;
};


MEDUSA_END;
