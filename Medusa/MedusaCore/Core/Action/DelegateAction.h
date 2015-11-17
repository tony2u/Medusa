// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInstantAction.h"
#include "Core/Pattern/Delegate.h"
MEDUSA_BEGIN;

class DelegateAction :public BaseInstantAction
{
public:
	typedef Delegate<void(void*)> DelegateType;
public:
	DelegateAction(DelegateType func, const StringRef& name = StringRef::Empty) :BaseInstantAction(name), mDelegate(func) {}
	virtual ~DelegateAction(void) {}
	virtual ActionType Type()const override { return ActionType::Instant; }
public:
	virtual DelegateAction* Clone()const override { return new DelegateAction(mDelegate); }
	virtual DelegateAction* Reverse()const override { return new DelegateAction(mDelegate); }
	static DelegateAction* Create(DelegateType func) { return new DelegateAction(func); }
protected:
	virtual bool OnAction()override
	{
		if (mDelegate)
		{
			mDelegate(this->mTarget);
		}
		return true;
	}
protected:
	DelegateType mDelegate;

};

MEDUSA_END;
