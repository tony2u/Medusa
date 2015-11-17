// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DropPoolGroup.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

DropPoolGroup::DropPoolGroup()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mPreventDuplicate = false;
	mMinTimes = 1;
	mMaxTimes = 1;
//SIREN_BODY_CONSTRUCT_END
}

DropPoolGroup::~DropPoolGroup()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DropPoolGroup, 13);
SIREN_PROPERTY_METADATA(0, DropPoolGroup, PreventDuplicate, 16, false);
SIREN_PROPERTY_METADATA(1, DropPoolGroup, MinTimes, 8, 1);
SIREN_PROPERTY_METADATA(2, DropPoolGroup, MaxTimes, 8, 1);
SIREN_PROPERTY_METADATA_STRUCT(3, DropPoolGroup, Items, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;