// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "TextureAtlas.h"

MEDUSA_BEGIN;


class MedusaTextureAtlas:public TextureAtlas
{
public:
	using TextureAtlas::TextureAtlas;
	virtual TextureAtlasType AtlasType()const { return TextureAtlasType::MedusaCustom; }
protected:
	virtual TextureAtlasPage* OnCreatePage(FileEntry& fileEntry, const FileIdRef& fileId, const IStream& stream) override;
protected:
	static TextureAtlasRegion* CreateAtlasRegion(const IStream& stream);
};

MEDUSA_END;
