// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "PackageInfo.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

PackageInfo::PackageInfo()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

PackageInfo::~PackageInfo()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(PackageInfo, 11);
SIREN_PROPERTY_METADATA_STRUCT(0, PackageInfo, Description, 11);
SIREN_PROPERTY_METADATA_STRUCT(1, PackageInfo, Path, 4);
SIREN_PROPERTY_METADATA_STRUCT(2, PackageInfo, Signature, 9);
//SIREN_BODY_METADATA_END

MEDUSA_END;