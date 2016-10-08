// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

//-------------------------------------------------------------------------
// The way the map is viewed.
//-------------------------------------------------------------------------
enum class TiledMapOrientation
{
	// This map is an orthogonal map.
	Orthogonal = 0x01,

	// This map is an isometric map.
	Isometric = 0x02,

	// This map is an isometric staggered map.
	Staggered = 0x03,

	// This map is an hexagonal staggered map.
	Hexagonal = 0x04
};

//-------------------------------------------------------------------------
// The order in which tiles on tile layers are rendered.
//-------------------------------------------------------------------------
enum class TiledMapRenderOrder
{
	// The default is TMX_RIGHT_DOWN.
	RightDown = 0x01,
	RightUp = 0x02,
	LeftDown = 0x03,
	LeftUp = 0x03
};

//-------------------------------------------------------------------------
// The stagger axis for the map. (only applies to hexagonal maps)
//-------------------------------------------------------------------------
enum class TiledMapStaggerAxis
{
	None = 0x00,  // if the map is not hexagonal
	X = 0x01,
	Y = 0x02
};

//-------------------------------------------------------------------------
// The stagger index for the map. (applies to hexagonal AND isometric staggered maps)
//-------------------------------------------------------------------------
enum class TiledMapStaggerIndex
{
	None = 0x00,  // if the map is not hexagonal
	Even = 0x01,
	Odd = 0x02
};

enum class TiledLayerType
{
	Tile = 0X01,
	Object = 0X02,
	Image = 0X04
};


namespace TiledMapProperties
{
	//layer:
	const extern StringRef EnableCollision;	//bool
	const extern StringRef EnableInput;	//bool

	const extern StringRef InstantiateLayer;	//string
	const extern StringRef ScriptFile;	//string

	//tile:
	const extern StringRef Capability;	//int collision capability
	const extern StringRef DirectionCapability;	//int direction capability

	//all
	const extern StringRef InstantiateMode;	//string enum:Mesh,Sprite
	const extern StringRef State;	//string enum: Done,Running,Paused

}

namespace TiledMapPropertyValues
{
	const extern StringRef Mesh;	//Instantiate enum
	const extern StringRef Sprite;	//Instantiate enum
	const extern StringRef Done;	//State enum
	const extern StringRef Running;	//State enum
	const extern StringRef Paused;	//State enum

}


MEDUSA_END;
