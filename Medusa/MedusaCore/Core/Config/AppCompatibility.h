// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Config/AppInitializeOperation.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class AppCompatibility
{
public:
	struct Schema;
	AppCompatibility();
	~AppCompatibility();
//SIREN_HEADER_COPY_BEGIN
public:
	AppCompatibility(const AppCompatibility& other)
	{
		mVersion = other.mVersion;
		mOperation = other.mOperation;
	}
	AppCompatibility& operator=(const AppCompatibility& other)
	{
		mVersion = other.mVersion;
		mOperation = other.mOperation;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(AppCompatibility);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, Version);
	SIREN_METHOD(AppInitializeOperation, Operation);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mVersion;
	AppInitializeOperation mOperation;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct AppCompatibility::Schema
{
	SIREN_PROPERTY(0, 0, Required, AppCompatibility, uint, mVersion);
	SIREN_PROPERTY(1, 1, Required, AppCompatibility, AppInitializeOperation, mOperation);
	SIREN_PROPERTIES_2(void,AppCompatibility);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;