// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DropPoolRandomItem.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

DropPoolRandomItem::DropPoolRandomItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mProbability = 1;
//SIREN_BODY_CONSTRUCT_END
}

DropPoolRandomItem::~DropPoolRandomItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DropPoolRandomItem, 18);
SIREN_FIELD_METADATA(0, DropPoolRandomItem, Probability, 11, 1, true);
//SIREN_BODY_METADATA_END

MEDUSA_END;