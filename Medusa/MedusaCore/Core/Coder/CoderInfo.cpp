// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "CoderInfo.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

CoderInfo::CoderInfo()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mType = (CoderType)0;
//SIREN_BODY_CONSTRUCT_END
}

CoderInfo::~CoderInfo()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(CoderInfo, 9);
SIREN_PROPERTY_METADATA(0, CoderInfo, Type, 4, (CoderType)0);
SIREN_PROPERTY_METADATA_STRUCT(1, CoderInfo, Data, 4);
//SIREN_BODY_METADATA_END

MEDUSA_END;