// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
MEDUSA_BEGIN;

class BlinkAction :public BaseFiniteAction
{
public:
	BlinkAction(float duration);
	virtual ~BlinkAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override;

	virtual BlinkAction* Clone()const override;
	virtual BlinkAction* Reverse()const override;

	static BlinkAction* Create(float duration);
};

MEDUSA_END;
