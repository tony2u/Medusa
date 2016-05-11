// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledMapFactory.h"


MEDUSA_BEGIN;

TiledMapFactory::TiledMapFactory()
{
}

TiledMapFactory::~TiledMapFactory()
{

}

bool TiledMapFactory::Initialize()
{
	return true;
}

bool TiledMapFactory::Uninitialize()
{
	Clear();
	return true;
}

TmxTiledMap* TiledMapFactory::Create(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		TmxTiledMap* val = (TmxTiledMap*)Find(fileId);
		RETURN_SELF_IF_NOT_NULL((TmxTiledMap*)val);
	}

	TmxTiledMap* model = new TmxTiledMap(fileId);
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

