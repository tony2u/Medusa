// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "DefaultRunnable.h"
MEDUSA_BEGIN;



DefaultRunnable::DefaultRunnable(RunningState state/*=RunningState::None*/) :mState(state)
{

}


DefaultRunnable::~DefaultRunnable()
{
	
}

bool DefaultRunnable::Start()
{
	mState = RunningState::Running;
	return true;
}

bool DefaultRunnable::Pause()
{
	switch (mState)
	{
		case RunningState::None:
			return false;
		case RunningState::Running:
			mState = RunningState::Paused;
			return true;
		case RunningState::Paused:
			return true;
		case RunningState::Done:
			return false;
	}
	return false;
}

bool DefaultRunnable::Resume()
{
	switch (mState)
	{
		case RunningState::None:
			return false;
		case RunningState::Paused:
			mState = RunningState::Running;
			return true;
		case RunningState::Running:
			return true;
		case RunningState::Done:
			return false;
	}
	return false;
}

bool DefaultRunnable::Stop()
{
	switch (mState)
	{
		case RunningState::Running:
			return true;
		case RunningState::Done:
			return false;
		default:
			mState = RunningState::Done;
			return true;
	}

}

bool DefaultRunnable::Reset()
{
	switch (mState)
	{
		case RunningState::Running:
		default:
			mState = RunningState::None;
			return true;
	}

}

void DefaultRunnable::ForceSetState(RunningState val)
{
	mState = val;
}


MEDUSA_END;