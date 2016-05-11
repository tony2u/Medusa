// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/SortedDictionary.h"
#include "Resource/TextureAtlas/TextureAtlasDefines.h"
#include "Geometry/Color4.h"
#include "Geometry/Rect2.h"

MEDUSA_BEGIN;

class RenderingObjectFactory :public Singleton<RenderingObjectFactory>
{
	friend class Singleton<RenderingObjectFactory>;
public:
	RenderingObjectFactory();
	~RenderingObjectFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	RenderingObject CreateFromTexture(const FileIdRef& textureName, const Rect2F& textureRect = Rect2F::Zero, const Color4F& color = Color4F::White);
	RenderingObject CreateFromTexture(ITexture* texture, const Rect2F& textureRect = Rect2F::Zero, const Color4F& color = Color4F::White);

	RenderingObject CreateNineGridTexture(const Size2F& targetSize, const FileIdRef& textureName, const ThicknessF& padding, const Rect2F& textureRect = Rect2F::Zero);
	RenderingObject CreateFromSingleTextureMaterial(IMaterial* material, const Rect2F& textureRect = Rect2F::Zero, const Color4F& color = Color4F::White);

	RenderingObject CreateFromTextureAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasType fileFormat = TextureAtlasType::None);
	RenderingObject CreateFromTextureAtlasRegion(TextureAtlasRegion* region, const Color4F& color = Color4F::White);


	bool CreateFromTextureAtlas(SortedDictionary<uint, RenderingObject>& outObjects, const StringRef& regionPattern, const FileIdRef& atlasFileId, TextureAtlasType fileFormat = TextureAtlasType::None, const Color4F& color = Color4F::White);
	bool CreateFromTextures(List<RenderingObject>& outObjects, const StringRef& textureNamePattern, const Color4F& color = Color4F::White);




};

MEDUSA_END;