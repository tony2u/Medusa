// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ISceneGraph.h"
#include "Node/Scene/IScene.h"
#include "Rendering/RenderQueue/IRenderQueue.h"
#include "Rendering/RenderingStatics.h"

MEDUSA_BEGIN;

ISceneGraph::ISceneGraph(IScene* scene)
	:mScene(scene), mRenderQueue(nullptr)
{

}


ISceneGraph::~ISceneGraph(void)
{
	Uninitialize();
}

void ISceneGraph::OnUpdate(float dt)
{
	RenderingStatics::Instance().IncreaseTotalNodeCount(mRenderQueue->NodeCount());

	//RETURN_IF_EQUAL(mChangedFlag, RenderableChangedFlags::None);
	if (mChangedFlag.Has(RenderableChangedFlags::RenderQueueChanged))
	{
		OnUpdateQueue();
		mChangedFlag.Remove(RenderableChangedFlags::RenderQueueChanged);
	}
	mRenderQueue->Update(mChangedFlag);
	mChangedFlag = RenderableChangedFlags::None;
}

bool ISceneGraph::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(FrameTask::Uninitialize());
	SAFE_DELETE(mRenderQueue);

	return true;
}




MEDUSA_END;
