// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IBrainBody.h"

MEDUSA_BEGIN;

IBrainBody::IBrainBody()
{
	mBrain = nullptr;
	mCurrentBehavior = nullptr;
}

IBrainBody::~IBrainBody(void)
{
	SAFE_RELEASE(mBrain);
}

bool IBrainBody::Behave(void* sender, float dt)
{
	RETURN_FALSE_IF_NULL(mBrain);

	if (mCurrentBehavior != nullptr)
	{
		RETURN_TRUE_IF_TRUE(mCurrentBehavior->Update(*this, sender, dt));
		mCurrentBehavior->Exit(*this, sender);
		mCurrentBehavior = nullptr;
	}

	const IBehavior* newBehavior = mBrain->Behave(*this, sender);
	if (mCurrentBehavior != newBehavior)
	{
		mCurrentBehavior = newBehavior;
		if (mCurrentBehavior != nullptr)
		{
			RETURN_TRUE_IF_TRUE(mCurrentBehavior->Update(*this, sender, dt));
			mCurrentBehavior->Exit(*this, sender);
			mCurrentBehavior = nullptr;
		}
	}


	return true;
}

bool IBrainBody::ReceiveEvent(void* sender, IEventArg& e)
{
	RETURN_FALSE_IF_NULL(mBrain);
	const IBehavior* newBehavior = mBrain->ReceiveEvent(*this, sender, e);
	if (newBehavior != nullptr)
	{
		if (mCurrentBehavior != nullptr)
		{
			mCurrentBehavior->Exit(*this, sender);
		}
		mCurrentBehavior = newBehavior;
	}

	return true;

}


void IBrainBody::TransferTo(const IBehavior* val, void* sender)
{
	if (mCurrentBehavior != nullptr)
	{
		mCurrentBehavior->Exit(*this, sender);
	}
	mCurrentBehavior = val;
	if (mCurrentBehavior != nullptr)
	{
		mCurrentBehavior->Enter(*this, sender);
	}
}

MEDUSA_END;