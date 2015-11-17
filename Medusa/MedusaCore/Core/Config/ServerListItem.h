// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Config/ServerUsageItem.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class ServerListItem
{
public:
	struct Schema;
	ServerListItem();
	~ServerListItem();
//SIREN_HEADER_COPY_BEGIN
public:
	ServerListItem(const ServerListItem& other)
	{
		mUsages = other.mUsages;
		mId = other.mId;
	}
	ServerListItem& operator=(const ServerListItem& other)
	{
		mUsages = other.mUsages;
		mId = other.mId;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(ServerListItem);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_LIST(ServerUsageItem, Usages);
	SIREN_METHOD(uint, Id);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	List<ServerUsageItem> mUsages;
	uint mId;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct ServerListItem::Schema
{
	SIREN_PROPERTY_LIST(0, 0, Required, ServerListItem, ServerUsageItem, mUsages);
	SIREN_PROPERTY(1, 1, Required, ServerListItem, uint, mId);
	SIREN_PROPERTIES_2(void,ServerListItem);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;