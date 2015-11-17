// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FrameAutoStopWatch.h"
#include "Core/Profile/StopWatch.h"
#include "Application/ApplicationStatics.h"

MEDUSA_BEGIN;



FrameAutoStopWatch::FrameAutoStopWatch(StopWatch& watch, FrameStep step) :mStopWatch(watch), mStep(step)
{
	mStopWatch.Start();
}

FrameAutoStopWatch::~FrameAutoStopWatch()
{
	mStopWatch.Shot();
	ApplicationStatics::Instance().SetElpased(mStep, mStopWatch.ElapsedMilliseconds());
}

MEDUSA_END;