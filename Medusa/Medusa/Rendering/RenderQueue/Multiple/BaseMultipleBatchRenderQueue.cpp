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


BaseMultipleBatchRenderQueue::BaseMultipleBatchRenderQueue(IRenderTarget* renderTarget/*=nullptr*/, Camera* camera/*=nullptr*/)
{
	mRenderGroup = new SceneRenderGroup(renderTarget, camera);

}

BaseMultipleBatchRenderQueue::~BaseMultipleBatchRenderQueue(void)
{
	mRenderGroup->Uninitialize();
	SAFE_DELETE(mRenderGroup);
}


void BaseMultipleBatchRenderQueue::Update(RenderableChangedFlags changedFlag)
{
	RETURN_IF_EQUAL(changedFlag, RenderableChangedFlags::None);
	if (mIsNeedToSort)
	{
		Linq::InsertSortByOtherCompare<IRenderable*, EqualCompare<IRenderable*>,IRenderableCompareByRenderingPriority>(mNodes);
		mIsNeedToSort = false;
	}

	if (changedFlag.Has(RenderableChangedFlags::BatchChanged))
	{
		OnUpdateBatchList();
		OnUpdateRenderGroup();
		mIsCommandChanged = true;
	}

	mIsCommandChanged |= OnUpdateBatchData();
}

void BaseMultipleBatchRenderQueue::SetCamera(Camera* val)
{
	mRenderGroup->SetCamera(val);
}

Camera* BaseMultipleBatchRenderQueue::GetCamera() const
{
	return mRenderGroup->GetCamera();
}

void BaseMultipleBatchRenderQueue::SetRenderTarget(IRenderTarget* val)
{
	mRenderGroup->SetRenderTarget(val);
}

IRenderTarget* BaseMultipleBatchRenderQueue::RenderTarget() const
{
	return mRenderGroup->RenderTarget();
}

bool BaseMultipleBatchRenderQueue::OnUpdateBatchList()
{
	BatchList& fontBatches = mBatches.MutableFront();
	BatchList& backBatches = mBatches.MutableBack();

	BatchGroup currentBatchGroup = 0;
	IRenderBatch* currentBatch = nullptr;
	FOR_EACH_COLLECTION(i, mNodes)
	{
		IRenderable* node = *i;
		BatchGroup group = node->GetBatchGroup();
#ifdef MEDUSA_SAFE_CHECK
		if (group==0)
		{
			Log::AssertFailedFormat("Error batch group");
		}
#endif

		if (group != currentBatchGroup)
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
	FOR_EACH_COLLECTION(i, fontBatches)
	{
		IRenderBatch* batch = *i;
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
	FOR_EACH_COLLECTION(i, mBatches.MutableFront())
	{
		IRenderBatch* batch = *i;
		isChanged|=batch->Update();
	}
	return isChanged;
}



MEDUSA_END;