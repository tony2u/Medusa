// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Siren/ISirenConfig.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class PackageInfo : public ISirenConfig<PackageInfo>
{
public:
	struct Schema;
	PackageInfo();
	~PackageInfo();

	SIREN_COMMON(PackageInfo);
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(HeapString, Description);
	SIREN_METHOD(HeapString, Path);
	SIREN_METHOD(HeapString, Signature);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	HeapString mDescription;
	HeapString mPath;
	HeapString mSignature;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct PackageInfo::Schema
{
	SIREN_PROPERTY(0, 0, Required, PackageInfo, HeapString, mDescription);
	SIREN_PROPERTY(1, 1, Required, PackageInfo, HeapString, mPath);
	SIREN_PROPERTY(2, 2, Required, PackageInfo, HeapString, mSignature);
	SIREN_PROPERTIES_3(void,PackageInfo);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;