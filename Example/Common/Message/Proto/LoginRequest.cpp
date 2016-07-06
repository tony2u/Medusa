// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "LoginRequest.h"
//SIREN_BODY_INCLUDE_END

LoginRequest::LoginRequest()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mOrder = 0;
//SIREN_BODY_CONSTRUCT_END
}

LoginRequest::~LoginRequest()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(LoginRequest, 12);
SIREN_FIELD_METADATA_STRUCT(0, LoginRequest, Name, 4);
SIREN_FIELD_METADATA(1, LoginRequest, Order, 5, 0, false);
//SIREN_BODY_METADATA_END

