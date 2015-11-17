// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Task/Task.h"

MEDUSA_BEGIN;


class FrameTask :public Task
{
public:
	FrameTask(ExecuteOption option = ExecuteOption::Async);
	~FrameTask(void);

	void Update(float dt);
protected:
	virtual void OnSelfExecute()override;
	virtual void OnUpdate(float dt);
protected:
	volatile float mInterval;
};

MEDUSA_END;
