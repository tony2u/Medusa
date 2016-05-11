// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "ServiceInfo.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

ServiceInfo::ServiceInfo()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mId = 0;
	mPort = 0;
	mType = (ServiceType)0;
//SIREN_BODY_CONSTRUCT_END
}

ServiceInfo::~ServiceInfo()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(ServiceInfo, 11);
SIREN_FIELD_METADATA(0, ServiceInfo, Id, 2, 0, false);
SIREN_FIELD_METADATA_STRUCT(1, ServiceInfo, Host, 4);
SIREN_FIELD_METADATA(2, ServiceInfo, Port, 4, 0, false);
SIREN_FIELD_METADATA(3, ServiceInfo, Type, 4, (ServiceType)0, false);
SIREN_FIELD_METADATA_STRUCT(4, ServiceInfo, Options, 7);
//SIREN_BODY_METADATA_END

MEDUSA_END;