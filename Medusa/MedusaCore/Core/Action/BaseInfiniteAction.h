// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/IAction.h"

MEDUSA_BEGIN;

class BaseInfiniteAction :public IAction
{
public:
	BaseInfiniteAction(const StringRef& name = StringRef::Empty) :IAction(name) {}
	virtual ~BaseInfiniteAction(void) {}
	virtual ActionType Type()const { return ActionType::Infinite; }
};
MEDUSA_END;
