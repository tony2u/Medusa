// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "StringId.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

StringId::StringId()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mId = 0;
	mCheck1 = 0;
	mCheck2 = 0;
//SIREN_BODY_CONSTRUCT_END
}

StringId::~StringId()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(StringId, 8);
SIREN_PROPERTY_METADATA(0, StringId, Id, 2, 0);
SIREN_PROPERTY_METADATA(1, StringId, Check1, 6, 0);
SIREN_PROPERTY_METADATA(2, StringId, Check2, 6, 0);
//SIREN_BODY_METADATA_END

MEDUSA_END;