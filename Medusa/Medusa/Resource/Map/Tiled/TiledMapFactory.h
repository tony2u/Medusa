// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Map/Tiled/TmxTiledMap.h"

MEDUSA_BEGIN;



class TiledMapFactory :public Singleton<TiledMapFactory>, public BaseResourceFactory < TmxTiledMap >
{
	friend class Singleton < TiledMapFactory > ;
public:
	TiledMapFactory();
	~TiledMapFactory();
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	TmxTiledMap* Create(const FileIdRef& fileId, ResourceShareType shareType = ResourceShareType::Share);
private:

};

MEDUSA_END;