// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DropPoolItemLimit.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

DropPoolItemLimit::DropPoolItemLimit()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mItemId = 0;
	mType = 0;
	mMinCount = 0;
	mMaxCount = 0;
//SIREN_BODY_CONSTRUCT_END
}

DropPoolItemLimit::~DropPoolItemLimit()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DropPoolItemLimit, 17);
SIREN_FIELD_METADATA(0, DropPoolItemLimit, ItemId, 6, 0, false);
SIREN_FIELD_METADATA(1, DropPoolItemLimit, Type, 4, 0, true);
SIREN_FIELD_METADATA(2, DropPoolItemLimit, MinCount, 8, 0, false);
SIREN_FIELD_METADATA(3, DropPoolItemLimit, MaxCount, 8, 0, false);
//SIREN_BODY_METADATA_END

MEDUSA_END;