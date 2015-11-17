// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "UpdateServer.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

UpdateServer::UpdateServer()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mMinAppVersion = 0;
	mCurFileVersion = 0;
	mStatus = (UpdateServerStatus)0;
//SIREN_BODY_CONSTRUCT_END
}

UpdateServer::~UpdateServer()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(UpdateServer, 12);
SIREN_PROPERTY_METADATA(0, UpdateServer, MinAppVersion, 13, 0);
SIREN_PROPERTY_METADATA(1, UpdateServer, CurFileVersion, 14, 0);
SIREN_PROPERTY_METADATA_STRUCT(2, UpdateServer, Description, 11);
SIREN_PROPERTY_METADATA(3, UpdateServer, Status, 6, (UpdateServerStatus)0);
SIREN_PROPERTY_METADATA_STRUCT(4, UpdateServer, Patches, 7);
SIREN_PROPERTY_METADATA_STRUCT(5, UpdateServer, JumpPatches, 11);
//SIREN_BODY_METADATA_END

MEDUSA_END;