// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Core/Pattern/Delegate.h"
#include "Graphics/GraphicsTypes.h"
#include "TextureAtlasDefines.h"
#include "Core/Pattern/Object/ArrayObjectFactory.h"
#include "Core/Pattern/Object/MapObjectFactory.h"


MEDUSA_BEGIN;

class TextureAtlasFactory :public Singleton<TextureAtlasFactory>, public BaseResourceFactory < TextureAtlas >
{
	friend class Singleton < TextureAtlasFactory >;
	using FormatObjectFactory = ArrayObjectFactory<(size_t)TextureAtlasType::Count, size_t, TextureAtlas*(const FileIdRef& fileId)>;

public:
	TextureAtlasFactory();
	~TextureAtlasFactory();
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	TextureAtlas* CreateEmpty(const FileIdRef& fileId, ResourceShareType shareType = ResourceShareType::Share);

	TextureAtlas* Create(const FileIdRef& fileId, TextureAtlasType fileFormat = TextureAtlasType::None, ResourceShareType shareType = ResourceShareType::Share);
	TextureAtlas* CreateTiledAtlas(const FileIdRef& textureFileId, const Size2U textureSize, const Size2U& tileSize, ResourceShareType shareType = ResourceShareType::Share);

	TextureAtlasRegion* CreateAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasType fileFormat = TextureAtlasType::None);
	TextureAtlasRegion* CreateAtlasRegion(int regionId, const FileIdRef& atlasFileId, TextureAtlasType fileFormat = TextureAtlasType::None);

	static TextureAtlasType TryGetAtlasType(const StringRef& fileName);
private:
	
private:
	FormatObjectFactory mObjectFactory;


};

MEDUSA_END;