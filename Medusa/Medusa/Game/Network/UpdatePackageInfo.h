// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Siren/ISirenConfig.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class UpdatePackageInfo
{
public:
	struct Schema;
	UpdatePackageInfo();
	~UpdatePackageInfo();
//SIREN_HEADER_COPY_BEGIN
public:
	UpdatePackageInfo(const UpdatePackageInfo& other)
	{
		mDescription = other.mDescription;
		mPath = other.mPath;
		mSignature = other.mSignature;
	}
	UpdatePackageInfo& operator=(const UpdatePackageInfo& other)
	{
		mDescription = other.mDescription;
		mPath = other.mPath;
		mSignature = other.mSignature;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(UpdatePackageInfo);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_STRING(HeapString, Description);
	SIREN_STRING(HeapString, Path);
	SIREN_STRING(HeapString, Signature);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	HeapString mDescription;
	HeapString mPath;
	HeapString mSignature;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct UpdatePackageInfo::Schema
{
	SIREN_FIELD(0, 0, Required, UpdatePackageInfo, HeapString, mDescription);
	SIREN_FIELD(1, 1, Required, UpdatePackageInfo, HeapString, mPath);
	SIREN_FIELD(2, 2, Required, UpdatePackageInfo, HeapString, mSignature);
	SIREN_FIELDS_3(void,UpdatePackageInfo);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;