// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "IRunnable.h"
MEDUSA_BEGIN;


class DefaultRunnable :public IRunnable
{
public:
	DefaultRunnable(RunningState state = RunningState::None);
	virtual ~DefaultRunnable();
public:
	virtual RunningState State() const override { return mState; }
	virtual bool IsRunning()const override { return mState == RunningState::Running; }
	virtual bool IsDone()const override { return mState == RunningState::Done; }
	virtual bool Start()override;
	virtual bool Pause()override;
	virtual bool Resume()override;
	virtual bool Stop()override;
	virtual bool Reset()override;

	bool ForceIsRunning()const { return mState == RunningState::Running; }
	bool ForceIsDone()const { return mState == RunningState::Done; }
	RunningState ForceGetState() const { return mState; }
	void ForceSetState(RunningState val);

protected:
	RunningState mState = RunningState::None;
};

MEDUSA_END;