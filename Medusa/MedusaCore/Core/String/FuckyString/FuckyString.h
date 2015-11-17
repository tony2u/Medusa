// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/String/FuckyString/FuckyStringNode.h"
//SIREN_HEADER_INCLUDE_END
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/IO/IFileLoadable.h"
MEDUSA_BEGIN;

class FuckyString :public Singleton<FuckyString>, public IFileLoadable
{
	friend class Singleton<FuckyString>;
public:
	struct Schema;
	FuckyString();
	~FuckyString();

//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_DICTIONARY(int, FuckyStringNode, RootNodes);
//SIREN_HEADER_METHOD_END
	bool Initialize(const FileIdRef& fileId, uint format = 0);

	virtual bool LoadFromData(StringRef path, const MemoryByteData& data, uint format = 0)override;
	virtual void Unload()override;


	bool IsFucky(StringRef str)const;
	bool IsFucky(WStringRef str)const;
	bool TryClean(WHeapString& str, char replace = '*')const;

//SIREN_HEADER_FIELD_BEGIN
protected:
	Dictionary<int, FuckyStringNode> mRootNodes;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct FuckyString::Schema
{
	SIREN_PROPERTY_DICTIONARY(0, 0, Required, FuckyString, int, FuckyStringNode, mRootNodes);
	SIREN_PROPERTIES_1(void,FuckyString);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;