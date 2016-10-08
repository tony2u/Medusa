// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;


enum class ResourceType
{
	Image = 0,
	Audio,
	Material,
	Texture,
	Font,
	Shader,
	Camera,
	Effect,
	Timeline,
	Model,
	RenderPass,
	Light,
	RenderTarget,
	TextureAtlas,
	Skeleton,
	TiledMap,
	Tileset,
	DataSource,


	Count = 18
};

enum class ResourceShareType
{
	None = 0,
	Share = 1,
	ShareAndCache = 2
};

enum class InstantiateMode
{
	None,
	Sprite,
	Mesh
};

MEDUSA_END;
