// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/Composite/BaseSingleCompositeFiniteAction.h"

MEDUSA_BEGIN;
class CountDownAction :public BaseSingleCompositeFiniteAction
{
public:
	CountDownAction(IAction* innerAction, float duration) :BaseSingleCompositeFiniteAction(innerAction, duration) {}
	virtual ~CountDownAction(void) {}
};
MEDUSA_END;
