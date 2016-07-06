// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseMultipleBatchRenderQueue.h"
#include "Rendering/IRenderable.h"
#include "Core/Log/Log.h"
#include "Rendering/Scene/SceneRenderGroup.h"
#include "Rendering/Command/IRenderingCommand.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Core/Collection/Linq.h"
#include "Rendering/Batch/BatchPool.h"

MEDUSA_BEGIN;

int IRenderableCompareByRenderingPriority::Compare(IRenderable* t1, IRenderable* t2)
{
	return (int)t1->GetRenderingPriority() - (int)t2->GetRenderingPriority();
}


BaseMultipleBatchRenderQueue::BaseMultipleBatchRenderQueue(const Share<IRenderTarget>& renderTarget/*=nullptr*/, const Share<Camera>& camera/*=nullptr*/)
{
	mRenderGroup = new SceneRenderGroup(renderTarget, camera);

}

BaseMultipleBatchRenderQueue::~BaseMultipleBatchRenderQueue(void)
{
	BatchList& fontBatches = mBatches.MutableFront();
	BatchList& backBatches = mBatches.MutableBack();
	FOR_EACH_ITEM_CLEAR(fontBatches, BatchPool::Instance().Recycle);
	FOR_EACH_ITEM_CLEAR(backBatches, BatchPool::Instance().Recycle);

	mRenderGroup->Uninitialize();
	SAFE_DELETE(mRenderGroup);
}


void BaseMultipleBatchRenderQueue::Update(RenderableChangedFlags changedFlag)
{
	RETURN_IF_EQUAL(changedFlag, RenderableChangedFlags::None);
	if (mIsNeedToSort)
	{
		Linq::InsertSortByOtherCompare<IRenderable*, EqualCompare,IRenderableCompareByRenderingPriority>(mNodes);
		mIsNeedToSort = false;
	}

	if (MEDUSA_FLAG_HAS(changedFlag,RenderableChangedFlags::BatchChanged))
	{
		OnUpdateBatchList();
		OnUpdateRenderGroup();
		mIsCommandChanged = true;
	}

	mIsCommandChanged |= OnUpdateBatchData();
}

void BaseMultipleBatchRenderQueue::SetCamera(const Share<Camera>& val)
{
	mRenderGroup->SetCamera(val);
}

const Share<Camera>& BaseMultipleBatchRenderQueue::GetCamera() const
{
	return mRenderGroup->GetCamera();
}

void BaseMultipleBatchRenderQueue::SetRenderTarget(const Share<IRenderTarget>& val)
{
	mRenderGroup->SetRenderTarget(val);
}

const Share<IRenderTarget>& BaseMultipleBatchRenderQueue::RenderTarget() const
{
	return mRenderGroup->RenderTarget();
}

bool BaseMultipleBatchRenderQueue::OnUpdateBatchList()
{
	BatchList& fontBatches = mBatches.MutableFront();
	BatchList& backBatches = mBatches.MutableBack();

	BatchGroup currentBatchGroup = 0;
	IRenderBatch* currentBatch = nullptr;
	for(auto node: mNodes)
	{
		BatchGroup group = node->GetBatchGroup();
#ifdef MEDUSA_SAFE_CHECK
		if (group==0)
		{
			Log::AssertFailedFormat("Error batch group");
		}
#endif

		if (!group.IsMatch(currentBatchGroup))
		{
			BatchList::NodePtr prevBatch = fontBatches.FindFirstWithOtherKey<BatchGroup, IRenderBatchCompareToBatchGroup>(group);
			if (prevBatch != nullptr)
			{
				//found original batch
				if (currentBatch!=nullptr)
				{
					currentBatch->Freeze();
				}

				currentBatch = prevBatch->Value;
				currentBatch->Prepare();
				backBatches.Add(currentBatch);
				fontBatches.Delete(prevBatch);
			}
			else
			{
				//create a new one
				currentBatch = BatchPool::Instance().Create(node);
				currentBatch->Prepare();
				backBatches.Add(currentBatch);
			}
			currentBatchGroup = group;
		}

		if (!currentBatch->IsAvailableFor(*node))
		{
			if (currentBatch != nullptr)
			{
				currentBatch->Freeze();
			}

			currentBatch = BatchPool::Instance().Create(node);
			currentBatch->Prepare();
			backBatches.Add(currentBatch);
		}
		currentBatch->AddNode(node);

	}

	//clear front batches
	FOR_EACH_ITEM_CLEAR(fontBatches, BatchPool::Instance().Recycle);
	mBatches.Swap();


	return true;
}


bool BaseMultipleBatchRenderQueue::OnUpdateRenderGroup()
{
	mRenderGroup->Uninitialize();
	BatchList& fontBatches = mBatches.MutableFront();
	for(auto batch: fontBatches)
	{
		mRenderGroup->Add(batch);
	}
	return true;
}

bool BaseMultipleBatchRenderQueue::OnUpdateCommands(RenderingFlags renderingFlags /*= RenderingFlags::None*/)
{
	mCommands.Clear();
	mRenderGroup->Draw(*this,renderingFlags);
	return true;
}

bool BaseMultipleBatchRenderQueue::OnUpdateBatchData()
{
	bool isChanged = false;
	for(auto batch:mBatches.MutableFront())
	{
		isChanged|=batch->Update();
	}
	return isChanged;
}



MEDUSA_END;