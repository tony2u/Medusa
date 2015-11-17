// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/INode.h"
#include "Core/Collection/Queue.h"
#include "Core/Collection/List.h"
#include "Core/Task/FrameTask.h"

MEDUSA_BEGIN;




class ISceneGraph :public FrameTask
{
public:
	ISceneGraph(IScene* scene);
	virtual ~ISceneGraph(void);

public:
	virtual bool Initialize()override { return true; }
	virtual bool Uninitialize()override;
protected:
	virtual void OnUpdate(float dt)override;
	virtual bool OnUpdateQueue() { return true; }
public:
	IScene* Scene() const { return mScene; }
	IRenderQueue* RenderQueue() const { return mRenderQueue; }

	RenderableChangedFlags ChangedFlag() const { return mChangedFlag; }
	void SetChangedFlag(RenderableChangedFlags val) { mChangedFlag = val; }
protected:
	IScene* mScene;
	IRenderQueue* mRenderQueue;
	RenderableChangedFlags mChangedFlag;
	
};

MEDUSA_END;
