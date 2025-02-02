// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Scene/SceneRenderGroup.h"
#include "Rendering/Effect/EffectRenderGroup.h"
#include "Rendering/Effect/EffectRenderGroupPool.h"

#include "Node/Scene/SceneGraph/ISceneGraph.h"
#include "Rendering/RenderingContext.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Core/Log/Log.h"
#include "Resource/Camera/Camera.h"


MEDUSA_BEGIN;


SceneRenderGroup::SceneRenderGroup(const Share<IRenderTarget>& renderTarget, const Share<Camera>& camera)
	:mRenderTarget(renderTarget),
	mCamera(camera)
{
	
}


SceneRenderGroup::~SceneRenderGroup()
{

}


bool SceneRenderGroup::Initialize()
{
	return true;
}

bool SceneRenderGroup::Uninitialize()
{
	FOR_EACH_TO(mGroups, Uninitialize());
	FOR_EACH_ITEM_CLEAR(mGroups, EffectRenderGroupPool::Instance().Recycle);
	return true;
}

bool SceneRenderGroup::Add(IRenderBatch* batch)
{
	EffectRenderGroup* group = nullptr;
	if (mGroups.IsEmpty())
	{
		group = EffectRenderGroupPool::Instance().Create();
		group->SetEffect(batch->Effect());
		mGroups.Add(group);
	}
	else
	{
		group = mGroups.Last();
		if (group->Effect() != batch->Effect())
		{
			group = EffectRenderGroupPool::Instance().Create();
			group->SetEffect(batch->Effect());
			mGroups.Add(group);
		}
	}

	group->Add(batch);
	return true;
}

void SceneRenderGroup::Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags/*=RenderingFlags::None*/)
{
	RETURN_IF_EMPTY(mGroups);
	RenderingContext::Instance().ApplyRenderTargetAndCamera(mRenderTarget, mCamera);

	if (!MEDUSA_FLAG_HAS(renderingFlags,RenderingFlags::KeepRenderTarget))
	{
		mRenderTarget->Clear();
	}
	mRenderTarget->OnBeforeDraw();

	for (auto group : mGroups)
	{
		group->Draw(renderQueue, renderingFlags);
	}

	mRenderTarget->OnAfterDraw();
	RenderingContext::Instance().RestoreRenderTargetAndCamera();

}

void SceneRenderGroup::Print(HeapString& ioStr, uint level)
{
	ioStr.AppendLine();
	ioStr.Append('\t', level);
	for (auto group : mGroups)
	{
		group->Print(ioStr, level + 1);
	}

	Log::Info(ioStr);
}




MEDUSA_END;