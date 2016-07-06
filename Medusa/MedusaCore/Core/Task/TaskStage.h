// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Threading/ThreadingDefines.h"

MEDUSA_BEGIN;


class TaskStage:public IInitializable
{
public:
	TaskStage();
	~TaskStage(void);

	void Register(Task* task);
	void Clear();

	void Start();
	void Wait();

	void StartAndWait();

	void SetOption(ExecuteOption option);
protected:
	List<Task*> mTasks;
};

MEDUSA_END;
