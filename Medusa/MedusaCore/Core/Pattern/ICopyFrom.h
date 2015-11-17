// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;

template<typename T>
struct ICopyFrom
{
	virtual ~ICopyFrom() {}
	virtual bool CopyFrom(const T& val) = 0;
};

MEDUSA_END;