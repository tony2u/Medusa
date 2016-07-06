// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

struct INonCopyable
{
	INonCopyable() = default;
	~INonCopyable() = default;

private:
	INonCopyable(const INonCopyable&) = delete;
	INonCopyable& operator=(const INonCopyable&) = delete;

	//INonCopyable(INonCopyable&&) = delete;
	//INonCopyable& operator=(INonCopyable&&) = delete;
};

MEDUSA_END;