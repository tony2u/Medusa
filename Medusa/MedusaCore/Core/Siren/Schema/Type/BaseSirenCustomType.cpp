// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BaseSirenCustomType.h"

MEDUSA_BEGIN;

BaseSirenCustomType::BaseSirenCustomType()
{

}

BaseSirenCustomType::~BaseSirenCustomType(void)
{

}

void BaseSirenCustomType::SetParentType(BaseSirenCustomType* val)
{
	RETURN_IF_EQUAL(mParentType, val);
	mParentType = val;

	if (mParentType != nullptr)
	{
		mFullName = mParentType->FullName() + "." + mName;
	}
	else
	{
		mFullName = mName;
	}
}


MEDUSA_END;