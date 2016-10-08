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
	switch (mState)
	{
	case RunningState::None:
		mState = RunningState::Running;
		OnStart();
	case RunningState::Running:
		return true;
	case RunningState::Paused:
		Resume();
		return true;
	case RunningState::Done:
		Reset();
		mState = RunningState::Running;
		OnStart();
		return true;
	}

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
		OnPause();
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
		OnResume();
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
	case RunningState::Done:
		return true;
	default:
		mState = RunningState::Done;
		OnStop();
		return true;
	}

}

bool DefaultRunnable::Reset()
{
	switch (mState)
	{
	case RunningState::None:
		return true;
	default:
		mState = RunningState::None;
		OnReset();
		return true;
	}

}

bool DefaultRunnable::SetState(RunningState val)
{
	switch (val)
	{
	case RunningState::Running:
		if (mState==RunningState::Paused)
		{
			return Resume();
		}
		return Start();
	case RunningState::None:
		return Reset();
	case RunningState::Paused:
		return Pause();
	case RunningState::Done:
		return Stop();
	}

	return true;
}


MEDUSA_END;