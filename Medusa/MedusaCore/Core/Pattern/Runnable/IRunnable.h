// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;


/*
None	->	(Start)	->	Running
None	->	(Stop)	->	Done

Running	->	(Reset)	->	None
Running	->	(Pause)	->	Paused
Running	->	(Stop)	->	Done

Paused	->	(Reset)	->	None
Paused	->	(Resume)	->	Running
Paused	->	(Stop)	->	Done

Done	->	(Reset)	->	None
Done	->	(Reset,Stop)	->	Running

*/

enum class RunningState
{
	Done = -2,
	Paused = -1,
	None = 0,
	Running = 1
};

struct IRunnable
{
	virtual ~IRunnable() {}
	virtual RunningState State() const = 0;
	virtual bool IsRunning()const = 0;
	virtual bool IsDone()const = 0;
	virtual bool Start() = 0;	//start from beginning
	virtual bool Pause() = 0;	//pause
	virtual bool Resume() = 0;	//resume 
	virtual bool Stop() = 0;	//stop at the end
	virtual bool Reset() = 0;	//reset at beginning
	bool Restart()
	{
		RETURN_FALSE_IF_FALSE(Reset());
		return Start();
	}
};

MEDUSA_END;