// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Network/Message/Service/ServerStatus.h"
#include "Core/Network/Message/Service/ServiceInfo.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class ServerConfigItem
{
public:
	struct Schema;
	ServerConfigItem();
	~ServerConfigItem();
//SIREN_HEADER_COPY_BEGIN
public:
	ServerConfigItem(const ServerConfigItem& other)
	{
		mId = other.mId;
		mName = other.mName;
		mDescription = other.mDescription;
		mStatus = other.mStatus;
		mServices = other.mServices;
	}
	ServerConfigItem& operator=(const ServerConfigItem& other)
	{
		mId = other.mId;
		mName = other.mName;
		mDescription = other.mDescription;
		mStatus = other.mStatus;
		mServices = other.mServices;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(ServerConfigItem);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, Id);
	SIREN_METHOD(HeapString, Name);
	SIREN_METHOD(HeapString, Description);
	SIREN_METHOD(ServerStatus, Status);
	SIREN_METHOD_DICTIONARY(uint, ServiceInfo, Services);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mId;
	HeapString mName;
	HeapString mDescription;
	ServerStatus mStatus;
	Dictionary<uint, ServiceInfo> mServices;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct ServerConfigItem::Schema
{
	SIREN_FIELD(0, 0, Required, ServerConfigItem, uint, mId);
	SIREN_FIELD(1, 1, Required, ServerConfigItem, HeapString, mName);
	SIREN_FIELD(2, 2, Required, ServerConfigItem, HeapString, mDescription);
	SIREN_FIELD(3, 3, Required, ServerConfigItem, ServerStatus, mStatus);
	SIREN_FIELD_DICTIONARY(4, 4, Required, ServerConfigItem, uint, ServiceInfo, mServices);
	SIREN_FIELDS_5(void,ServerConfigItem);
};

//SIREN_HEADER_SCHEMA_END

MEDUSA_END;