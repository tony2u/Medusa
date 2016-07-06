// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/INonCopyable.h"
MEDUSA_BEGIN;



class AutoStopWatch :public INonCopyable
{
public:
	AutoStopWatch(StopWatch& watch);
	~AutoStopWatch();
protected:
	StopWatch& mStopWatch;

};


MEDUSA_END;