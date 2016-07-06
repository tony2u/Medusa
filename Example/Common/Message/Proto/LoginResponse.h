// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"
USING_MEDUSA;

//SIREN_HEADER_INCLUDE_BEGIN
//SIREN_HEADER_INCLUDE_END

class LoginResponse
{
public:
	struct Schema;
	LoginResponse();
	~LoginResponse();
//SIREN_HEADER_COPY_BEGIN
public:
	LoginResponse(const LoginResponse& other)
	{
		mError = other.mError;
	}
	LoginResponse& operator=(const LoginResponse& other)
	{
		mError = other.mError;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(LoginResponse);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(int, Error);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	int mError;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct LoginResponse::Schema
{
	SIREN_FIELD(0, 0, Required, LoginResponse, int, mError);
	SIREN_FIELDS_1(void,LoginResponse);
};

//SIREN_HEADER_SCHEMA_END

