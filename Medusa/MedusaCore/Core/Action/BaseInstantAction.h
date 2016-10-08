// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/IAction.h"

MEDUSA_BEGIN;

class BaseInstantAction :public IAction
{
public:
	BaseInstantAction(const StringRef& name = StringRef::Empty) :IAction(name) {}
	virtual ~BaseInstantAction(void) {}
	virtual ActionType Type()const { return ActionType::Instant; }
public:
	virtual bool Start()
	{
		RETURN_FALSE_IF_FALSE(DefaultRunnable::Start());
		bool result = OnAction();
		this->Stop();
		return result;
	}
protected:
	virtual bool OnAction() = 0;
};

MEDUSA_END;
