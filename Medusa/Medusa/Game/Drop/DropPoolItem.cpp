// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DropPoolItem.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

DropPoolItem::DropPoolItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mId = 0;
	mType = 0;
	mCount = 1;
//SIREN_BODY_CONSTRUCT_END
}

DropPoolItem::~DropPoolItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DropPoolItem, 12);
SIREN_PROPERTY_METADATA(0, DropPoolItem, Id, 2, 0);
SIREN_PROPERTY_METADATA(1, DropPoolItem, Type, 4, 0);
SIREN_PROPERTY_METADATA(2, DropPoolItem, Count, 5, 1);
//SIREN_BODY_METADATA_END

MEDUSA_END;