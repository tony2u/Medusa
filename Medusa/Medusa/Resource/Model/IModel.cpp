// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IModel.h"


MEDUSA_BEGIN;


IModel::IModel(const FileIdRef& fileId/*=FileId::Empty*/)
	:IResource(fileId),mType(ModelType::Unknown)
	
{
}


IModel::~IModel(void)
{
	
}


void IModel::CustomDraw( IRenderable* node,RenderingFlags renderingFlags/*=RenderingFlags::None*/ )
{
	/*FOR_EACH_COLLECTION(i,mMeshes)
	{
	BaseMesh* mesh=*i;
	IMaterial* material= mesh->GetMaterial();
	IEffect* effect=material->GetEffect();
	RenderingItem renderingItem(node,mesh);
	CustomDrawRenderBatch batch;
	batch.Add(renderingItem);

	EffectTechnique* technique=effect->GetCurrentTechniqueGroup()->GetCurrentTechnique();
	EffectTechnique::PassCollectionType& renderPasses=technique->GetRenderPasses();
	FOR_EACH_COLLECTION(i,renderPasses)
	{
	IRenderPass* renderPass=*i;
	RenderingContext::Instance().ApplyRenderPass(renderPass);
	bool isContinue=renderPass->Draw(renderQueue, renderingFlags);
	if (isContinue)
	{
	RenderingContext::Instance().ApplyMaterial(material);

	RenderingContext::Instance().ApplyBatch(&batch);
	RenderingContext::Instance().ValidateBeforeDraw();
	batch.Draw(renderQueue, renderingFlags);
	RenderingContext::Instance().RestoreBatch();

	RenderingContext::Instance().RestoreMaterial();
	}

	RenderingContext::Instance().RestoreRenderPass();
	BREAK_IF_FALSE(isContinue);
	}
	}*/
}


void IModel::BatchDraw( IRenderable* node,IRenderBatch* batch,RenderingFlags renderingFlags/*=RenderingFlags::None*/ )
{
	/*FOR_EACH_COLLECTION(i,mMeshes)
	{
	BaseMesh* mesh=*i;
	IMaterial* material= mesh->GetMaterial();
	IEffect* effect=material->GetEffect();
	RenderingItem renderingItem(node,mesh);

	EffectTechnique* technique=effect->GetCurrentTechniqueGroup()->GetCurrentTechnique();
	EffectTechnique::PassCollectionType& renderPasses=technique->GetRenderPasses();
	FOR_EACH_COLLECTION(i,renderPasses)
	{
	IRenderPass* renderPass=*i;
	RenderingContext::Instance().ApplyRenderPass(renderPass);
	bool isContinue=renderPass->Draw(renderQueue, renderingFlags);
	if (isContinue)
	{
	RenderingContext::Instance().ApplyMaterial(material);

	RenderingContext::Instance().ApplyBatch(batch);
	RenderingContext::Instance().ValidateBeforeDraw();
	batch->Draw(renderQueue, renderingFlags);
	RenderingContext::Instance().RestoreBatch();

	RenderingContext::Instance().RestoreMaterial();
	}

	RenderingContext::Instance().RestoreRenderPass();
	BREAK_IF_FALSE(isContinue);
	}
	}*/
	
}



MEDUSA_END;