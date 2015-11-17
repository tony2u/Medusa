// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IPredicateBehavior.h"
#include "Core/Pattern/Predicate/PredicateConfig.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

IPredicateBehavior::IPredicateBehavior(const IPredicate* predicate /*= nullptr*/) :mPredicate(nullptr)
{

}

IPredicateBehavior::~IPredicateBehavior(void)
{
	SAFE_RELEASE(mPredicate);
}


void IPredicateBehavior::SetPredicate(const IPredicate* val)
{
	SAFE_ASSIGN_REF(mPredicate, val);
}


bool IPredicateBehavior::EvaluateBool(void* sender) const
{
	if (mPredicate != nullptr)
	{
		return mPredicate->EvaluateBool(sender);
	}
	return true;
}


int IPredicateBehavior::Evaluate(void* sender) const
{
	if (mPredicate != nullptr)
	{
		return mPredicate->Evaluate(sender);
	}
	return 1;
}

bool IPredicateBehavior::LoadFromXmlNode(pugi::xml_node node)
{
	RETURN_FALSE_IF_FALSE(IBehavior::LoadFromXmlNode(node));

	uint predicateId = node.attribute("Predicate").as_uint(0);

	if (predicateId != 0)
	{
		IPredicate* predicate = PredicateConfig::Instance().TryGetObjectWithFailed(predicateId, nullptr);
		Log::AssertNotNullFormat(predicate, "Cannot find predicate id:{}", predicateId);
		SetPredicate(predicate);
	}

	return true;
}


MEDUSA_IMPLEMENT_RTTI(IPredicateBehavior, IBehavior);

MEDUSA_END;