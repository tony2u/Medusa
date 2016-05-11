// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "TextureAtlas.h"
#include "Graphics/GraphicsTypes.h"


MEDUSA_BEGIN;


class SpineTextureAtlas:public TextureAtlas
{
public:
	using TextureAtlas::TextureAtlas;
	virtual TextureAtlasType AtlasType()const { return TextureAtlasType::Spine; }
protected:
	virtual TextureAtlasPage* OnCreatePage(const FileIdRef& fileId, const IStream& stream) override;
protected:
	static TextureAtlasRegion* CreateAtlasRegion(const IStream& stream);
	static GraphicsTextureMagFilter ToMagFilter(const StringRef& val);
	static GraphicsTextureMinFilter ToMinFilter(const StringRef& val);
	static GraphicsTextureWrapMode ToWrapS(const StringRef& val);
	static GraphicsTextureWrapMode ToWrapT(const StringRef& val);
};

MEDUSA_END;
