// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "StateTransitionMode.h"

MEDUSA_BEGIN;

class IStateConnector
{
public:
	IStateConnector();
	virtual ~IStateConnector(void);
public:
	IPredicate* Predicate() const { return mPredicate; }
	void SetPredicate(IPredicate* val) { mPredicate = val; }

	IState* State() const { return mState; }
	void SetState(IState* val) { mState = val; }

	StateTransitionMode TransitionMode() const { return mTransitionMode; }
	void SetTransitionMode(StateTransitionMode val) { mTransitionMode = val; }

	bool Evaluate(void* sender)const;
protected:
	IPredicate* mPredicate;
	IState* mState;
	StateTransitionMode mTransitionMode;
	
};

MEDUSA_END;
