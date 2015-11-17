// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Config/ServerUsageType.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class ServerUsageItem
{
public:
	struct Schema;
	ServerUsageItem();
	~ServerUsageItem();
//SIREN_HEADER_COPY_BEGIN
public:
	ServerUsageItem(const ServerUsageItem& other)
	{
		mUsage = other.mUsage;
		mServerId = other.mServerId;
	}
	ServerUsageItem& operator=(const ServerUsageItem& other)
	{
		mUsage = other.mUsage;
		mServerId = other.mServerId;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(ServerUsageItem);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(ServerUsageType, Usage);
	SIREN_METHOD(uint, ServerId);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	ServerUsageType mUsage;
	uint mServerId;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct ServerUsageItem::Schema
{
	SIREN_PROPERTY(0, 0, Required, ServerUsageItem, ServerUsageType, mUsage);
	SIREN_PROPERTY(1, 1, Required, ServerUsageItem, uint, mServerId);
	SIREN_PROPERTIES_2(void,ServerUsageItem);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;