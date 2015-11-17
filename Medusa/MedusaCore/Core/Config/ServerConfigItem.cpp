// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "ServerConfigItem.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

ServerConfigItem::ServerConfigItem()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mId = 0;
	mPort = 0;
	mStatus = (ServerStatus)0;
	mType = (ServerType)0;
//SIREN_BODY_CONSTRUCT_END
}

ServerConfigItem::~ServerConfigItem()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(ServerConfigItem, 16);
SIREN_PROPERTY_METADATA(0, ServerConfigItem, Id, 2, 0);
SIREN_PROPERTY_METADATA_STRUCT(1, ServerConfigItem, Address, 7);
SIREN_PROPERTY_METADATA(2, ServerConfigItem, Port, 4, 0);
SIREN_PROPERTY_METADATA(3, ServerConfigItem, Status, 6, (ServerStatus)0);
SIREN_PROPERTY_METADATA(4, ServerConfigItem, Type, 4, (ServerType)0);
//SIREN_BODY_METADATA_END

MEDUSA_END;