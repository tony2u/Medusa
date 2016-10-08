// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PredicateFactory.h"
#include "AndPredicate.h"
#include "OrPredicate.h"
#include "XorPredicate.h"
#include "NotPredicate.h"

#include "TruePredicate.h"
#include "FalsePredicate.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;




PredicateFactory::PredicateFactory()
{
	/*Register<AndPredicate>("AndPredicate");
	Register<OrPredicate>("OrPredicate");
	Register<XorPredicate>("XorPredicate");
	Register<NotPredicate>("NotPredicate");

	Register<TruePredicate>("TruePredicate");
	Register<FalsePredicate>("FalsePredicate");*/
}

IPredicate* PredicateFactory::SmartCreate(StringRef name)
{
	IPredicate* predicate = Create(name);
	if (predicate == nullptr)
	{
		predicate = Create(name + "Predicate");
	}
	Log::AssertNotNullFormat(predicate, "Cannot create predicate with type:{}", name.c_str());
	return predicate;
}

MEDUSA_END;