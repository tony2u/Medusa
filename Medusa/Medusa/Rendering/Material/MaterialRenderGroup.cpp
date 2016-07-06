// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Material/MaterialRenderGroup.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/Material/IMaterial.h"

#include "Rendering/RenderingContext.h"

#include "Rendering/IRenderable.h"
#include "Rendering/State/StateRenderGroup.h"
#include "Rendering/State/StateRenderGroupPool.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Rendering/RenderingStatics.h"


MEDUSA_BEGIN;


MaterialRenderGroup::MaterialRenderGroup()
	:mMaterial(nullptr)
{

}


MaterialRenderGroup::~MaterialRenderGroup()
{
}

bool MaterialRenderGroup::Initialize()
{
	return true;
}

bool MaterialRenderGroup::Uninitialize()
{
	FOR_EACH_TO(mGroups, Uninitialize());

	FOR_EACH_ITEM_CLEAR(mGroups, StateRenderGroupPool::Instance().Recycle);
	
	return true;
}


bool MaterialRenderGroup::Add(IRenderBatch* batch)
{
	StateRenderGroup* group = nullptr;
	if (mGroups.IsEmpty())
	{
		group = StateRenderGroupPool::Instance().Create();
		group->SetStateNode(batch->StateTreeNode());
		mGroups.Add(group);
	}
	else
	{
		group = mGroups.Last();
		if (group->StateNode()!=batch->StateTreeNode())
		{
			group = StateRenderGroupPool::Instance().Create();
			group->SetStateNode(batch->StateTreeNode());
			mGroups.Add(group);
		}
	}

	group->Add(batch);
	return true;
}

void MaterialRenderGroup::Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags/*=RenderingFlags::None*/)
{
	RenderingContext::Instance().ApplyMaterial(mMaterial);
	RenderingStatics::Instance().CountMaterial(mMaterial);
	RenderingStatics::Instance().CountMaterialTextures(mMaterial);

	for (auto group : mGroups)
	{
		group->Draw(renderQueue, renderingFlags);
	}

	RenderingContext::Instance().RestoreMaterial();
}


void MaterialRenderGroup::Print(HeapString& ioStr, uint level)
{
	ioStr.Append('\t', level);
	ioStr.AppendLine(mMaterial->Name().c_str());
	for (auto group : mGroups)
	{
		group->Print(ioStr, level + 1);
	}
}


MEDUSA_END;