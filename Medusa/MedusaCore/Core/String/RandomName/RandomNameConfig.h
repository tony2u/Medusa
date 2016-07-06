// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/String/RandomName/RandomNameConfigItem.h"
//SIREN_HEADER_INCLUDE_END
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/Singleton.h"

#include "Core/IO/IFileLoadSavable.h"
MEDUSA_BEGIN;

class RandomNameConfig :public Singleton<RandomNameConfig>, public IFileLoadSavable
{
	friend class Singleton < RandomNameConfig > ;
public:
	struct Schema;
	RandomNameConfig();
	~RandomNameConfig();

//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_LIST(RandomNameConfigItem, Items);
//SIREN_HEADER_METHOD_END
	bool Initialize(const FileIdRef& fileId, uint format = 0);

	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = 0)override;
	virtual void Unload()override;

	HeapString GetRandomName3(uint seed = 0)const;

//SIREN_HEADER_FIELD_BEGIN
protected:
	List<RandomNameConfigItem> mItems;
//SIREN_HEADER_FIELD_END
	Dictionary<size_t, List<const RandomNameConfigItem*>*> mItemDict;
};

//SIREN_HEADER_SCHEMA_BEGIN
struct RandomNameConfig::Schema
{
	SIREN_FIELD_LIST(0, 0, Required, RandomNameConfig, RandomNameConfigItem, mItems);
	SIREN_FIELDS_1(void,RandomNameConfig);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;