// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "AppCompatibility.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

AppCompatibility::AppCompatibility()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mVersion = 0;
	mOperation = (AppInitializeOperation)0;
//SIREN_BODY_CONSTRUCT_END
}

AppCompatibility::~AppCompatibility()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(AppCompatibility, 16);
SIREN_FIELD_METADATA(0, AppCompatibility, Version, 7, 0, false);
SIREN_FIELD_METADATA(1, AppCompatibility, Operation, 9, (AppInitializeOperation)0, false);
//SIREN_BODY_METADATA_END

MEDUSA_END;