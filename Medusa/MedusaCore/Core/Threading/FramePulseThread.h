// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/PulseThread.h"

MEDUSA_BEGIN;


class FramePulseThread:public PulseThread
{
public:
	FramePulseThread();
	~FramePulseThread(void);
	
	void Update(float dt);
protected:
	volatile float mInterval;
};

MEDUSA_END;
