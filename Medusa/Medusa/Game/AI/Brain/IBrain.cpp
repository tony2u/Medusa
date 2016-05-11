// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IBrain.h"
#include "Game/AI/Brain/IBrainMemory.h"

MEDUSA_BEGIN;




IBrain::IBrain()
{
	mRootBehavior = nullptr;
	mMemory = nullptr;
}

IBrain::~IBrain(void)
{
	SAFE_DELETE(mMemory);

	SAFE_RELEASE(mRootBehavior);
	SAFE_RELEASE_DICTIONARY_VALUE(mEventBehaviorDict);
}

const IBehavior* IBrain::Behave(IBrainBody& brainBody, void* sender)
{
	RETURN_NULL_IF_NULL(mRootBehavior);
	return mRootBehavior->Behave(brainBody, sender);
}

const IBehavior* IBrain::ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e)
{
	IBehavior* behavior = mEventBehaviorDict.GetOptional(e.Class().Name(), nullptr);
	RETURN_NULL_IF_NULL(behavior);
	return behavior->ReceiveEvent(brainBody, sender, e);
}

void IBrain::SetMemory(IBrainMemory* val)
{
	SAFE_ASSIGN(mMemory, val);
}

void IBrain::SetRootBehavior(IBehavior* val)
{
	SAFE_ASSIGN_REF(mRootBehavior, val);
}

bool IBrain::RegisterEventBehavior(const StringRef& eventName, IBehavior* val)
{
	if (mEventBehaviorDict.TryAdd(eventName, val))
	{
		SAFE_RETAIN(val);
		return true;
	}
	return false;
}

MEDUSA_IMPLEMENT_RTTI_ROOT(IBrain);


MEDUSA_END;