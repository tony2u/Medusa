// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Threading/ThreadingDefines.h"

MEDUSA_BEGIN;


class FrameTaskStage:public IInitializable
{
public:
	FrameTaskStage();
	~FrameTaskStage(void);

	virtual bool Initialize() override;
	virtual bool Uninitialize() override;

	void Add(FrameTask* task);
	void Clear();
	void Update(float dt);
	void Wait();

	void UpdateAndWait(float dt);

	void ApplyOptionToAll(ExecuteOption option);
protected:
	List<FrameTask*> mTasks;
};

MEDUSA_END;
