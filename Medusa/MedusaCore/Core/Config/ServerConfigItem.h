// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Config/ServerStatus.h"
#include "Core/Config/ServerType.h"
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
		mAddress = other.mAddress;
		mPort = other.mPort;
		mStatus = other.mStatus;
		mType = other.mType;
	}
	ServerConfigItem& operator=(const ServerConfigItem& other)
	{
		mId = other.mId;
		mAddress = other.mAddress;
		mPort = other.mPort;
		mStatus = other.mStatus;
		mType = other.mType;
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
	SIREN_METHOD(HeapString, Address);
	SIREN_METHOD(uint, Port);
	SIREN_METHOD(ServerStatus, Status);
	SIREN_METHOD(ServerType, Type);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mId;
	HeapString mAddress;
	uint mPort;
	ServerStatus mStatus;
	ServerType mType;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct ServerConfigItem::Schema
{
	SIREN_PROPERTY(0, 0, Required, ServerConfigItem, uint, mId);
	SIREN_PROPERTY(1, 1, Required, ServerConfigItem, HeapString, mAddress);
	SIREN_PROPERTY(2, 2, Required, ServerConfigItem, uint, mPort);
	SIREN_PROPERTY(3, 3, Required, ServerConfigItem, ServerStatus, mStatus);
	SIREN_PROPERTY(4, 4, Required, ServerConfigItem, ServerType, mType);
	SIREN_PROPERTIES_5(void,ServerConfigItem);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;