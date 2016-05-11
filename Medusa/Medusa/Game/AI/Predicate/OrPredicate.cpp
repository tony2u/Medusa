// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "OrPredicate.h"

MEDUSA_BEGIN;

OrPredicate::OrPredicate(const IPredicate* left /*= nullptr*/, const IPredicate* right /*= nullptr*/)
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

int OrPredicate::Evaluate(void* p) const
{
	RETURN_ZERO_IF_EMPTY(mItems);
	FOR_EACH_COLLECTION(i, mItems)
	{
		const IPredicate* item = *i;
		int r = item->Evaluate(p);
		if (r > 0)
		{
			return r;
		}
	}

	return 0;
}

MEDUSA_IMPLEMENT_RTTI(OrPredicate, IPredicate);

MEDUSA_END;