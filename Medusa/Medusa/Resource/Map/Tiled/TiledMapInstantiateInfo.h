// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Node/NodeInstantiateInfo.h"

MEDUSA_BEGIN;

class TiledMapInstantiateInfo :public NodeInstantiateInfo
{
	MEDUSA_RTTI(TiledMapInstantiateInfo, NodeInstantiateInfo);
public:
	using TileRefInstantiateDelegate = Delegate<INode*(const TiledTileRef& tiledRef, const RenderingObject& renderingObject, TiledMapInstantiateInfo* instantiateInfo)>;
public:
	TileRefInstantiateDelegate OnTileRefInstantiate;
	Point2I Offset{ 0,0 };
	bool UpdateSize = false;
};


MEDUSA_END;