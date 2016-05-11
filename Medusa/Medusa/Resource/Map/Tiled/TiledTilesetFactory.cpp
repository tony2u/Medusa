// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTilesetFactory.h"

MEDUSA_BEGIN;

TiledTilesetFactory::TiledTilesetFactory()
{
}

TiledTilesetFactory::~TiledTilesetFactory()
{

}

bool TiledTilesetFactory::Initialize()
{
	return true;
}

bool TiledTilesetFactory::Uninitialize()
{
	Clear();
	return true;
}

TiledTileset* TiledTilesetFactory::Create(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		TiledTileset* val = (TiledTileset*)Find(fileId);
		RETURN_SELF_IF_NOT_NULL((TiledTileset*)val);
	}

	TiledTileset* model = new TiledTileset(fileId);
	RETURN_NULL_IF_NULL(model);
	if (model->LoadFromFileSystem(fileId))
	{
		Add(model, shareType);
	}
	else
	{
		delete model;
		model = nullptr;
	}


	return model;
}

MEDUSA_END;

