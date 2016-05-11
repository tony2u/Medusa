// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Network/Message/Service/ServiceType.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class ServiceInfo
{
public:
	struct Schema;
	ServiceInfo();
	~ServiceInfo();
//SIREN_HEADER_COPY_BEGIN
public:
	ServiceInfo(const ServiceInfo& other)
	{
		mId = other.mId;
		mHost = other.mHost;
		mPort = other.mPort;
		mType = other.mType;
		mOptions = other.mOptions;
	}
	ServiceInfo& operator=(const ServiceInfo& other)
	{
		mId = other.mId;
		mHost = other.mHost;
		mPort = other.mPort;
		mType = other.mType;
		mOptions = other.mOptions;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(ServiceInfo);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, Id);
	SIREN_METHOD(HeapString, Host);
	SIREN_METHOD(ushort, Port);
	SIREN_METHOD(ServiceType, Type);
	SIREN_METHOD(HeapString, Options);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mId;
	HeapString mHost;
	ushort mPort;
	ServiceType mType;
	HeapString mOptions;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct ServiceInfo::Schema
{
	SIREN_FIELD(0, 0, Required, ServiceInfo, uint, mId);
	SIREN_FIELD(1, 1, Required, ServiceInfo, HeapString, mHost);
	SIREN_FIELD(2, 2, Required, ServiceInfo, ushort, mPort);
	SIREN_FIELD(3, 3, Required, ServiceInfo, ServiceType, mType);
	SIREN_FIELD(4, 4, Required, ServiceInfo, HeapString, mOptions);
	SIREN_FIELDS_5(void,ServiceInfo);
};

//SIREN_HEADER_SCHEMA_END

MEDUSA_END;