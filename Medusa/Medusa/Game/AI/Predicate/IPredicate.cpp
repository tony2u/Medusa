// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IPredicate.h"

MEDUSA_BEGIN;


IPredicate::IPredicate() :mId(0)
{

}

IPredicate::~IPredicate(void)
{
	Clear();

}

void IPredicate::Add(const IPredicate* item)
{
	mItems.Add(item); 
}

void IPredicate::Clear()
{
	SAFE_DELETE_COLLECTION(mItems);
}


MEDUSA_IMPLEMENT_RTTI_ROOT(IPredicate);

MEDUSA_END;