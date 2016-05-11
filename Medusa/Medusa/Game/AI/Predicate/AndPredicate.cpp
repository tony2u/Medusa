// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "AndPredicate.h"

MEDUSA_BEGIN;


AndPredicate::AndPredicate(const IPredicate* left /*= nullptr*/, const IPredicate* right /*= nullptr*/)
{
	if (left != nullptr)
	{
		Add(left);
	}

	if (right != nullptr)
	{
		Add(right);
	}
}


int AndPredicate::Evaluate(void* p) const
{
	RETURN_ZERO_IF_EMPTY(mItems);
	FOR_EACH_COLLECTION(i, mItems)
	{
		const IPredicate* item = *i;
		RETURN_ZERO_IF_ZERO(item->Evaluate(p));
	}

	return 1;
}

MEDUSA_IMPLEMENT_RTTI(AndPredicate, IPredicate);

MEDUSA_END;