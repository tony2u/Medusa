// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "ServerUsageItem.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

ServerUsageItem::ServerUsageItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mUsage = (ServerUsageType)0;
	mServerId = 0;
//SIREN_BODY_CONSTRUCT_END
}

ServerUsageItem::~ServerUsageItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(ServerUsageItem, 15);
SIREN_PROPERTY_METADATA(0, ServerUsageItem, Usage, 5, (ServerUsageType)0);
SIREN_PROPERTY_METADATA(1, ServerUsageItem, ServerId, 8, 0);
//SIREN_BODY_METADATA_END

MEDUSA_END;