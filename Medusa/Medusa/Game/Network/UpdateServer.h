// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Game/Network/UpdateServerStatus.h"
#include "Game/Network/UpdatePackageInfo.h"
#include "Core/Siren/ISirenConfig.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class UpdateServer : public ISirenConfig<UpdateServer>
{
public:
	struct Schema;
	UpdateServer();
	~UpdateServer();
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, MinAppVersion);
	SIREN_METHOD(uint, CurFileVersion);
	SIREN_STRING(HeapString, Description);
	SIREN_METHOD(UpdateServerStatus, Status);
	SIREN_METHOD_DICTIONARY(uint, UpdatePackageInfo, Patches);
	SIREN_METHOD_DICTIONARY(uint, UpdatePackageInfo, JumpPatches);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mMinAppVersion;
	uint mCurFileVersion;
	HeapString mDescription;
	UpdateServerStatus mStatus;
	Dictionary<uint, UpdatePackageInfo> mPatches;
	Dictionary<uint, UpdatePackageInfo> mJumpPatches;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct UpdateServer::Schema
{
	SIREN_FIELD(0, 0, Required, UpdateServer, uint, mMinAppVersion);
	SIREN_FIELD(1, 1, Required, UpdateServer, uint, mCurFileVersion);
	SIREN_FIELD(2, 2, Required, UpdateServer, HeapString, mDescription);
	SIREN_FIELD(3, 3, Required, UpdateServer, UpdateServerStatus, mStatus);
	SIREN_FIELD_DICTIONARY(4, 4, Required, UpdateServer, uint, UpdatePackageInfo, mPatches);
	SIREN_FIELD_DICTIONARY(5, 5, Required, UpdateServer, uint, UpdatePackageInfo, mJumpPatches);
	SIREN_FIELDS_6(void,UpdateServer);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;