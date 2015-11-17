// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BatchPool.h"
#include "Rendering/IRenderable.h"
#include "Rendering/Batch/Multiple/MultipleRenderBatch.h"
#include "Rendering/Batch/Single/SingleRenderBatch.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Application/Application.h"


MEDUSA_BEGIN;

IRenderBatch* BatchNewerById::New(RenderingStrategy id)
{
	switch (id)
	{
		case RenderingStrategy::MultipleDynamicBatch:
		case RenderingStrategy::MultipleStaticBatch:
			return new MultipleRenderBatch(id);
		case RenderingStrategy::SingleDynamicBatch:
		case RenderingStrategy::SingleStaticBatch:
			return new SingleRenderBatch(id);
		default:
			return nullptr;
	}
}


bool BatchPool::Initialize()
{
	return true;
}

bool BatchPool::Uninitialize()
{
	return true;
}

IRenderBatch* BatchPool::Create(IRenderable* node)
{
	IRenderBatch* batch = Create(node->GetRenderingStrategy());
	batch->Initialize();
	IMesh* mesh = node->Mesh();
	batch->SetEffect(mesh->Effect());
	batch->SetMaterial(mesh->Material());
	batch->SetDrawMode(mesh->DrawMode());
	batch->SetStateTreeNode(node->RenderStateTreeNode());
	batch->SetGroup(node->GetBatchGroup());
	mRecycledNodes.Remove(batch);
	return batch;
}

void BatchPool::Recycle(IRenderBatch* batch)
{
	batch->Uninitialize();
	batch->SetRecycleFrameCount(Application::Instance().FrameCount());
	mRecycledNodes.Add(batch);
	Recycle(batch->GetRenderingStrategy(), batch);
}

void BatchPool::Update(float dt)
{
	RETURN_IF_EMPTY(mRecycledNodes);
	uint64 frameCount = Application::Instance().FrameCount();

	auto head = mRecycledNodes.Head();
	auto tail = mRecycledNodes.Tail();
	for (auto i = head->Next; i != tail;)
	{
		IRenderBatch* batch = i->Value;
		if (frameCount - batch->RecycleFrameCount() >= mRecycleFrameDuration)
		{
			batch->ReleaseBuffer();
			i = mRecycledNodes.Remove(i);
		}
		else
		{
			i = i->Next;
		}
	}
}



MEDUSA_END;