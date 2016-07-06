// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/INonCopyable.h"
#include "Core/Chrono/StopWatch.h"
#include "Application/FrameStep.h"
MEDUSA_BEGIN;



class FrameAutoStopWatch :public INonCopyable
{
public:
	FrameAutoStopWatch(StopWatch& watch,FrameStep step);
	~FrameAutoStopWatch();
protected:
	StopWatch& mStopWatch;
	FrameStep mStep;

};


MEDUSA_END;