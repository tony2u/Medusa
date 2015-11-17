// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

//SIREN_BODY_INCLUDE_BEGIN
#include "ServerConfig.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
MEDUSA_BEGIN;

ServerConfig::ServerConfig()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

ServerConfig::~ServerConfig()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

void ServerConfig::Unload()
{
	mItems.Clear();
}

const ServerConfigItem* ServerConfig::GetServerConfigItem(uint id)const
{
	return mItems.TryGetValue(id);
}
//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(ServerConfig, 12);
SIREN_PROPERTY_METADATA_STRUCT(0, ServerConfig, Items, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;