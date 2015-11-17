// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"
MEDUSA_BEGIN;

class ProgressByAction:public BaseFiniteAction
{
public:
	ProgressByAction(float delta,float duration);
	virtual ~ProgressByAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override;
	virtual bool Initialize(void* target)override;

	virtual ProgressByAction* Clone()const override;
	virtual ProgressByAction* Reverse()const override;

	static ProgressByAction* Create(float delta,float duration);
private:
	float mDelta;
};

MEDUSA_END;
