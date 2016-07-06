// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IBrain.h"

MEDUSA_BEGIN;


class IBrainBody
{
protected:
	IBrainBody();
	virtual ~IBrainBody(void);
public:
	const Share<IBrain>& Brain() const { return mBrain; }
	void SetBrain(const Share<IBrain>& val) { mBrain = val; }

	const IBehavior* CurrentBehavior() const { return mCurrentBehavior; }

public:
	bool Behave(void* sender,float dt);
	bool ReceiveEvent(void* sender, IEventArg& e);

	void TransferTo(const IBehavior* val, void* sender);
protected:
	Share<IBrain> mBrain;
	const IBehavior* mCurrentBehavior;
};

MEDUSA_END;
