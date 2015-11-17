// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;

template<typename T>
struct INonCopyable
{
	INonCopyable() = default;
	~INonCopyable() = default;

	INonCopyable(const T&) = delete;
	T& operator=(const T&) = delete;

	INonCopyable(const T&&) = delete;
	T& operator=(const T&&) = delete;
};

MEDUSA_END;