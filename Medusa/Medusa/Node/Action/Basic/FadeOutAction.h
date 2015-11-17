// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
MEDUSA_BEGIN;

class FadeOutAction:public BaseFiniteAction
{
public:
	FadeOutAction(float duration);
	virtual ~FadeOutAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override;

	virtual FadeOutAction* Clone()const override;
	virtual IAction* Reverse()const override;

	static FadeOutAction* Create(float duration);
};

MEDUSA_END;
