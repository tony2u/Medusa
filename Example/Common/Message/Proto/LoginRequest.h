// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"
USING_MEDUSA;

//SIREN_HEADER_INCLUDE_BEGIN
//SIREN_HEADER_INCLUDE_END

class LoginRequest
{
public:
	struct Schema;
	LoginRequest();
	~LoginRequest();
//SIREN_HEADER_COPY_BEGIN
public:
	LoginRequest(const LoginRequest& other)
	{
		mName = other.mName;
		mOrder = other.mOrder;
	}
	LoginRequest& operator=(const LoginRequest& other)
	{
		mName = other.mName;
		mOrder = other.mOrder;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(LoginRequest);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_STRING(HeapString, Name);
	SIREN_METHOD(uint, Order);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	HeapString mName;
	uint mOrder;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct LoginRequest::Schema
{
	constexpr static uint Id{ 1 };
	SIREN_FIELD(0, 0, Required, LoginRequest, HeapString, mName);
	SIREN_FIELD(1, 1, Required, LoginRequest, uint, mOrder);
	SIREN_FIELDS_2(void,LoginRequest);
};

//SIREN_HEADER_SCHEMA_END

