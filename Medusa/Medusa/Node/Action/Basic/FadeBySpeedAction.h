// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInfiniteAction.h"
MEDUSA_BEGIN;

class FadeBySpeedAction:public BaseInfiniteAction
{
public:
	FadeBySpeedAction(float speed);
	virtual ~FadeBySpeedAction(void);
public:
	virtual bool Update(float dt, float blend = 1.f)override;

	virtual FadeBySpeedAction* Clone()const override;
	virtual FadeBySpeedAction* Reverse()const override;

	static FadeBySpeedAction* Create(float speed);
private:
	float mSpeed;
};

MEDUSA_END;
