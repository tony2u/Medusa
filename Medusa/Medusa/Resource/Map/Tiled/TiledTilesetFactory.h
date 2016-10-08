// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Map/Tiled/TiledTileset.h"

MEDUSA_BEGIN;



class TiledTilesetFactory :public Singleton<TiledTilesetFactory>, public BaseResourceFactory < TiledTileset >
{
	friend class Singleton < TiledTilesetFactory > ;
public:
	TiledTilesetFactory();
	~TiledTilesetFactory();
public:
	virtual StringRef Name()const override { return "TiledTilesetFactory"; }

	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	Share<TiledTileset> Create(const FileIdRef& fileId, ResourceShareType shareType = ResourceShareType::Share);
private:

};

MEDUSA_END;