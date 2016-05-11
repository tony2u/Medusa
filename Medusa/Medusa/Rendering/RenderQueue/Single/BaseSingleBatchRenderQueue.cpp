// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseSingleBatchRenderQueue.h"
#include "Rendering/IRenderable.h"
#include "Core/Log/Log.h"
#include "Rendering/Command/IRenderingCommand.h"
#include "Rendering/RenderDevice.h"
#include "Rendering/RenderEngine.h"
#include "Resource/Camera/Camera.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Rendering/Batch/BatchPool.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Rendering/RenderingContext.h"
#include <Resource/Material/IMaterial.h>

MEDUSA_BEGIN;


BaseSingleBatchRenderQueue::BaseSingleBatchRenderQueue(IRenderTarget* renderTarget /*= nullptr*/, Camera* camera /*= nullptr*/, RenderingStrategy strategy /*= RenderingStrategy::MultipleDynamicBatch*/)
	:mRenderTarget(renderTarget), mCamera(camera)
{
	SAFE_RETAIN(mRenderTarget);
	SAFE_RETAIN(mCamera);

	mBatch = BatchPool::Instance().Create(strategy);
	mBatch->Initialize();
}

BaseSingleBatchRenderQueue::~BaseSingleBatchRenderQueue(void)
{
	SAFE_RELEASE(mRenderTarget);
	SAFE_RELEASE(mCamera);

	BatchPool::Instance().Recycle(mBatch);
}

void BaseSingleBatchRenderQueue::SetRenderTarget(IRenderTarget* val)
{
	SAFE_ASSIGN_REF(mRenderTarget, val);
}

void BaseSingleBatchRenderQueue::SetCamera(Camera* val)
{
	SAFE_ASSIGN_REF(mCamera, val);
}

void BaseSingleBatchRenderQueue::Update(RenderableChangedFlags changedFlag)
{
	RETURN_IF_EQUAL(changedFlag, RenderableChangedFlags::None);

	if (MEDUSA_FLAG_HAS(changedFlag, RenderableChangedFlags::BatchChanged)|| MEDUSA_FLAG_HAS(changedFlag, RenderableChangedFlags::RenderQueueChanged))
	{
		mBatch->Prepare();
		if (!mNodes.IsEmpty())
		{
			IRenderable* node = mNodes.First();
			mBatch->SetEffect(node->Material()->Effect());
			mBatch->SetMaterial(node->Material());
			mBatch->SetDrawMode(node->Material()->DrawMode());
			mBatch->SetStateTreeNode(node->RenderStateTreeNode());
		}

		FOR_EACH_COLLECTION(i, mNodes)
		{
			mBatch->AddNode(*i);
		}

		mIsCommandChanged = true;
	}
	
	mIsCommandChanged |= mBatch->Update();
}

bool BaseSingleBatchRenderQueue::OnUpdateCommands(RenderingFlags renderingFlags /*= RenderingFlags::None*/)
{
	mCommands.Clear();

	RenderingContext::Instance().ApplyRenderTargetAndCamera(mRenderTarget, mCamera);
	if (!MEDUSA_FLAG_HAS(renderingFlags,RenderingFlags::KeepRenderTarget))
	{
		LOG_ASSERT_NOT_NULL(mRenderTarget);
		mRenderTarget->Clear();
	}

	mBatch->CustomDraw(*this);
	RenderingContext::Instance().RestoreRenderTargetAndCamera();
	return true;
}


MEDUSA_END;