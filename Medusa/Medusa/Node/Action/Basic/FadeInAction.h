// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
MEDUSA_BEGIN;

class FadeInAction:public BaseFiniteAction
{
public:
	FadeInAction(float duration);
	virtual ~FadeInAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override;

	virtual FadeInAction* Clone()const override;
	virtual IAction* Reverse()const override;

	static FadeInAction* Create(float duration);
};

MEDUSA_END;
