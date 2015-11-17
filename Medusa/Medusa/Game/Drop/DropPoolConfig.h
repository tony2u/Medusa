// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Game/Drop/DropPool.h"
#include "Core/Siren/ISirenConfig.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class DropPoolConfig : public ISirenConfig<DropPoolConfig>
{
public:
	struct Schema;
	DropPoolConfig();
	~DropPoolConfig();
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(DropPoolConfig);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_DICTIONARY_EX(uint, DropPool, Items);
//SIREN_HEADER_METHOD_END
public:
	bool Generate(uint id, List<DropPoolItem>& outItems, void* userData=nullptr)const;
	const DropPoolItem* GenerateFixedSingle(uint id)const;

//SIREN_HEADER_FIELD_BEGIN
protected:
	Dictionary<uint, DropPool> mItems;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct DropPoolConfig::Schema
{
	SIREN_PROPERTY_DICTIONARY(0, 0, Required, DropPoolConfig, uint, DropPool, mItems);
	SIREN_PROPERTIES_1(void,DropPoolConfig);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;