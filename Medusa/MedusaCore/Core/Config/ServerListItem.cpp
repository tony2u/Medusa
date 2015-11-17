// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "ServerListItem.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

ServerListItem::ServerListItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mId = 0;
//SIREN_BODY_CONSTRUCT_END
}

ServerListItem::~ServerListItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(ServerListItem, 14);
SIREN_PROPERTY_METADATA_STRUCT(0, ServerListItem, Usages, 6);
SIREN_PROPERTY_METADATA(1, ServerListItem, Id, 2, 0);
//SIREN_BODY_METADATA_END

MEDUSA_END;