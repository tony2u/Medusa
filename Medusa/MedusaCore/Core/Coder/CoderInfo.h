// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Coder/CoderType.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class CoderInfo
{
public:
	struct Schema;
	CoderInfo();
	~CoderInfo();
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(CoderType, Type);
	SIREN_METHOD(MemoryData, Data);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	CoderType mType;
	MemoryData mData;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct CoderInfo::Schema
{
	SIREN_FIELD(0, 0, Required, CoderInfo, CoderType, mType);
	SIREN_FIELD(1, 1, Optional, CoderInfo, MemoryData, mData);
	SIREN_FIELDS_2(void,CoderInfo);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;