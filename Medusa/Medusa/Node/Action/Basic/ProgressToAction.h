// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;
class ProgressToAction:public BaseFiniteAction
{
public:
	ProgressToAction(float endPercent,float duration);
	ProgressToAction(float beginPercent,float endPercent,float duration);

	virtual ~ProgressToAction(void);
public:
	virtual bool Reset() override;
	virtual bool Start() override;

	virtual bool Update(float dt, float blend = 1.f)override;
	virtual bool Initialize(void* target)override;
public:
	virtual ProgressToAction* Clone()const override;
	virtual ProgressToAction* Reverse()const override;

	static ProgressToAction* Create(float percent,float duration);
private:
	float mBeginPercent;
	float mEndPercent;
	float mDelta;
};

MEDUSA_END;
