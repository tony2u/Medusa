// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Effect/EffectRenderGroup.h"
#include "Rendering/Material/MaterialRenderGroup.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Effect/EffectTechniqueGroup.h"
#include "Resource/Effect/EffectTechnique.h"
#include "Resource/Effect/Pass/IRenderPass.h"
#include "Rendering/Material/MaterialRenderGroupPool.h"
#include "Rendering/RenderingContext.h"
#include "Rendering/IRenderable.h"
#include "Rendering/RenderingStatics.h"
#include "Rendering/Batch/IRenderBatch.h"

MEDUSA_BEGIN;


EffectRenderGroup::EffectRenderGroup()
	:mEffect(nullptr)
{

}


EffectRenderGroup::~EffectRenderGroup()
{
}

void EffectRenderGroup::SetEffect(const IEffect* val)
{
	SAFE_ASSIGN_REF(mEffect, val);
}


bool EffectRenderGroup::Initialize()
{
	return true;
}

bool EffectRenderGroup::Uninitialize()
{
	FOR_EACH_ITEM_TO(mGroups, Uninitialize());

	FOR_EACH_ITEM_CLEAR(mGroups, MaterialRenderGroupPool::Instance().Recycle);
	SAFE_RELEASE(mEffect);
	return true;
}

bool EffectRenderGroup::Add(IRenderBatch* batch)
{
	MaterialRenderGroup* group = nullptr;
	if (mGroups.IsEmpty())
	{
		group = MaterialRenderGroupPool::Instance().Create();
		group->SetMaterial(batch->Material());
		mGroups.Add(group);
	}
	else
	{
		group = mGroups.Last();
		if (group->Material() != batch->Material())
		{
			group = MaterialRenderGroupPool::Instance().Create();
			group->SetMaterial(batch->Material());
			mGroups.Add(group);
		}
	}

	group->Add(batch);
	return true;
}


void EffectRenderGroup::Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags/*=RenderingFlags::None*/)
{
	EffectTechnique* technique = mEffect->CurrentTechniqueGroup()->CurrentTechnique();
	EffectTechnique::PassCollectionType& renderPasses = technique->RenderPasses();
	RenderingStatics::Instance().CountRenderPass(renderPasses.Count());

	FOR_EACH_COLLECTION(i, renderPasses)
	{
		IRenderPass* renderPass = *i;
		RenderingContext::Instance().ApplyRenderPass(renderPass);
		bool isContinue = renderPass->Draw(renderQueue, renderingFlags);
		if (isContinue)
		{
			FOR_EACH_COLLECTION(j, mGroups)
			{
				MaterialRenderGroup* materialRenderGroup = *j;
				materialRenderGroup->Draw(renderQueue, renderingFlags);
			}
		}

		RenderingContext::Instance().RestoreRenderPass();
		BREAK_IF_FALSE(isContinue);
	}
}

void EffectRenderGroup::Print(HeapString& ioStr, uint level)
{
	ioStr.Append('\t', level);
	ioStr.AppendLine(mEffect->Name().c_str());
	FOR_EACH_COLLECTION(i, mGroups)
	{
		MaterialRenderGroup* materialRenderList = *i;
		materialRenderList->Print(ioStr, level + 1);
	}
}





MEDUSA_END;