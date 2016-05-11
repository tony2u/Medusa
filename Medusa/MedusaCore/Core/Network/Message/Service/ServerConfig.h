// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Network/Message/Service/ServerConfigItem.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class ServerConfig
{
public:
	struct Schema;
	ServerConfig();
	~ServerConfig();
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_DICTIONARY(uint, ServerConfigItem, Items);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	Dictionary<uint, ServerConfigItem> mItems;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct ServerConfig::Schema
{
	SIREN_FIELD_DICTIONARY(0, 0, Required, ServerConfig, uint, ServerConfigItem, mItems);
	SIREN_FIELDS_1(void,ServerConfig);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;