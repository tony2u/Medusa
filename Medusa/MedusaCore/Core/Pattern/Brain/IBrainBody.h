// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IBrain.h"

MEDUSA_BEGIN;


class IBrainBody
{
protected:
	IBrainBody();
	virtual ~IBrainBody(void);
public:
	IBrain* Brain() const { return mBrain; }
	void SetBrain(IBrain* val) { SAFE_ASSIGN_REF(mBrain, val); }

	const IBehavior* CurrentBehavior() const { return mCurrentBehavior; }

public:
	bool Behave(void* sender,float dt);
	bool ReceiveEvent(void* sender, IEventArg& e);

	void TransferTo(const IBehavior* val, void* sender);
protected:
	IBrain* mBrain;
	const IBehavior* mCurrentBehavior;
};

MEDUSA_END;
