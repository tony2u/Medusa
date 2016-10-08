// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Point2.h"
#include "Core/Pattern/Delegate.h"
#include "Geometry/GeometryDefines.h"

MEDUSA_BEGIN;

struct TiledTileRef
{
	using InstantiateDelegate = Delegate<INode*(const TiledTileRef&, const RenderingObject&)>;
	const static uint FlippedHorizontallyFlag = 0x80000000;
	const static uint FlippedVerticallyFlag = 0x40000000;
	const static uint FlippedDiagonallyFlag = 0x20000000;

	TiledTileRef();
	bool operator<(const TiledTileRef& val)const { return mPosition < val.mPosition; }
	bool operator==(const TiledTileRef& val)const { return mPosition == val.mPosition; }

	// Will take a gid and read the attributes from the first
	// two bits of it.
	void Initialize(const Point2I& position, uint globalId, const TiledTilesetRef* tilesetRef);

	uint TileId()const;
	const TiledTile* Tile() const { return mTile; }
	const Point2I& Position() const { return mPosition; }
	int X()const { return mPosition.X; }
	int Y()const { return mPosition.Y; }


	bool FlippedHorizontally() const { return (mTileGlobalId & FlippedHorizontallyFlag) != 0; }
	bool FlippedVertically() const { return (mTileGlobalId & FlippedVerticallyFlag) != 0; }
	bool FlippedDiagonally() const { return (mTileGlobalId & FlippedDiagonallyFlag) != 0; }

	INode* Instantiate(NodeInstantiateInfo* instantiateInfo = nullptr)const;
	int Capability() const;
	MoveDirection DirectionCapability() const;

	TiledTileLayer* Layer() const { return mLayer; }
	void SetLayer(TiledTileLayer* val) { mLayer = val; }
protected:
	Point2I mPosition;	//Y from down to top
	const TiledTile* mTile = nullptr;
	uint mTileGlobalId;
	TiledTileLayer* mLayer=nullptr;
	

};

MEDUSA_END;