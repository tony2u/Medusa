// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IStateConnector.h"
#include "Core/Pattern/Predicate/IPredicate.h"

MEDUSA_BEGIN;

IStateConnector::IStateConnector()
{
	mPredicate = nullptr;
	mState = nullptr;
	mTransitionMode = StateTransitionMode::Replace;
}

IStateConnector::~IStateConnector(void)
{
	
}

bool IStateConnector::Evaluate(void* sender)const
{
	if (mPredicate!=nullptr)
	{
		return mPredicate->EvaluateBool(sender);
	}
	return true;
}

MEDUSA_END;

