// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DropPoolConfig.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

DropPoolConfig::DropPoolConfig()
{
	//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

DropPoolConfig::~DropPoolConfig()
{
	//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

bool DropPoolConfig::Generate(uint id, List<DropPoolItem>& outItems, void* userData/*=nullptr*/) const
{
	const DropPool* dropPool = Find(id);
	Log::AssertNotNullFormat(dropPool, "Cannot find drop pool id:{}", id);
	RETURN_FALSE_IF_NULL(dropPool);
	return dropPool->Generate(*this, outItems, userData);
}

const DropPoolItem* DropPoolConfig::GenerateFixedSingle(uint id) const
{
	const DropPool* dropPool = Find(id);
	Log::AssertNotNullFormat(dropPool, "Cannot find drop pool id:{}", id);
	RETURN_NULL_IF_NULL(dropPool);
	return dropPool->GenerateFixedSingle();
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DropPoolConfig, 14);
SIREN_FIELD_METADATA_STRUCT(0, DropPoolConfig, Items, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;