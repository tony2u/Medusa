// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Config/UpdateServerStatus.h"
#include "Core/Config/PackageInfo.h"
#include "Core/Siren/ISirenConfig.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class UpdateServer
{
public:
	struct Schema;
	UpdateServer();
	~UpdateServer();
//SIREN_HEADER_COPY_BEGIN
public:
	UpdateServer(const UpdateServer& other)
	{
		mMinAppVersion = other.mMinAppVersion;
		mCurFileVersion = other.mCurFileVersion;
		mDescription = other.mDescription;
		mStatus = other.mStatus;
		mPatches = other.mPatches;
		mJumpPatches = other.mJumpPatches;
	}
	UpdateServer& operator=(const UpdateServer& other)
	{
		mMinAppVersion = other.mMinAppVersion;
		mCurFileVersion = other.mCurFileVersion;
		mDescription = other.mDescription;
		mStatus = other.mStatus;
		mPatches = other.mPatches;
		mJumpPatches = other.mJumpPatches;

		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(UpdateServer);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, MinAppVersion);
	SIREN_METHOD(uint, CurFileVersion);
	SIREN_METHOD(HeapString, Description);
	SIREN_METHOD(UpdateServerStatus, Status);
	SIREN_METHOD_DICTIONARY(uint, PackageInfo, Patches);
	SIREN_METHOD_DICTIONARY(uint, PackageInfo, JumpPatches);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mMinAppVersion;
	uint mCurFileVersion;
	HeapString mDescription;
	UpdateServerStatus mStatus;
	Dictionary<uint, PackageInfo> mPatches;
	Dictionary<uint, PackageInfo> mJumpPatches;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct UpdateServer::Schema
{
	SIREN_PROPERTY(0, 0, Required, UpdateServer, uint, mMinAppVersion);
	SIREN_PROPERTY(1, 1, Required, UpdateServer, uint, mCurFileVersion);
	SIREN_PROPERTY(2, 2, Required, UpdateServer, HeapString, mDescription);
	SIREN_PROPERTY(3, 3, Required, UpdateServer, UpdateServerStatus, mStatus);
	SIREN_PROPERTY_DICTIONARY(4, 4, Required, UpdateServer, uint, PackageInfo, mPatches);
	SIREN_PROPERTY_DICTIONARY(5, 5, Required, UpdateServer, uint, PackageInfo, mJumpPatches);
	SIREN_PROPERTIES_6(void,UpdateServer);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;