// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "XorPredicate.h"
#include "PredicateFactory.h"

MEDUSA_BEGIN;


XorPredicate::XorPredicate(const IPredicate* left /*= nullptr*/, const IPredicate* right /*= nullptr*/)
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

int XorPredicate::Evaluate(void* p) const
{
	RETURN_ZERO_IF_EMPTY(mItems);
	uintp count = mItems.Count();
	int result = mItems.First()->Evaluate(p);

	FOR_EACH_SIZE_BEGIN_END(i, 1, count - 1)
	{
		const IPredicate* item = mItems[i];
		result ^= item->Evaluate(p);
	}
	return result;
}

MEDUSA_IMPLEMENT_PREDICATE(XorPredicate);
MEDUSA_END;