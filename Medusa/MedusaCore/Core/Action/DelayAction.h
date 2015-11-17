// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;

class DelayAction :public BaseFiniteAction
{
public:
	DelayAction(float duration, const StringRef& name = StringRef::Empty) :BaseFiniteAction(duration, name) {}
	virtual ~DelayAction(void) {}
	virtual ActionType Type()const override { return ActionType::Finite; }
public:
	virtual DelayAction* Clone()const override { return new DelayAction(this->mDuration); }
	virtual DelayAction* Reverse()const override { return new DelayAction(this->mDuration); }
	static DelayAction* Create(float duration) { return new DelayAction(duration); }
};

MEDUSA_END;
