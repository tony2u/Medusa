// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "RandomNameConfigItem.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

RandomNameConfigItem::RandomNameConfigItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mPosition = 0;
//SIREN_BODY_CONSTRUCT_END
}

RandomNameConfigItem::~RandomNameConfigItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(RandomNameConfigItem, 20);
SIREN_FIELD_METADATA(0, RandomNameConfigItem, Position, 8, 0, false);
SIREN_FIELD_METADATA_STRUCT(1, RandomNameConfigItem, Value, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;