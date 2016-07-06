// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "LoginResponse.h"
//SIREN_BODY_INCLUDE_END

LoginResponse::LoginResponse()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mError = 0;
//SIREN_BODY_CONSTRUCT_END
}

LoginResponse::~LoginResponse()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(LoginResponse, 13);
SIREN_FIELD_METADATA(0, LoginResponse, Error, 5, 0, false);
//SIREN_BODY_METADATA_END

