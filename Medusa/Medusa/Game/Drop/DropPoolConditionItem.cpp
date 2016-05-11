// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DropPoolConditionItem.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

DropPoolConditionItem::DropPoolConditionItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mPredicateId = 0;
//SIREN_BODY_CONSTRUCT_END
}

DropPoolConditionItem::~DropPoolConditionItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DropPoolConditionItem, 21);
SIREN_FIELD_METADATA(0, DropPoolConditionItem, PredicateId, 11, 0, false);
SIREN_FIELD_METADATA_STRUCT(1, DropPoolConditionItem, Item, 4);
//SIREN_BODY_METADATA_END

MEDUSA_END;