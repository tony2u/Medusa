// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Rendering/IRenderable.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Material/IMaterial.h"
#include "Graphics/State/Tree/RenderStateTreeLeafNode.h"
#include "Resource/Effect/EffectTechniqueGroup.h"
#include "Resource/Effect/EffectTechnique.h"

#include "Rendering/RenderingContext.h"
#include "Rendering/RenderingStatics.h"


MEDUSA_BEGIN;


IRenderBatch::IRenderBatch(RenderingStrategy renderingStrategy)
	:mModelMatrix(Matrix::Identity),
	mRenderingStrategy(renderingStrategy),
	mIsFreezed(false),
	mEffect(nullptr),
	mMaterial(nullptr),
	mStateTreeNode(nullptr),
	mDrawMode(GraphicsDrawMode::Triangles)
{
}


IRenderBatch::~IRenderBatch()
{

}


bool IRenderBatch::IsAvailableFor(const IRenderable& node) const
{
	IMesh* mesh = node.Mesh();
	return IsAvailableFor(mesh->VertexCount(), mesh->IndexCount());
}

bool IRenderBatch::Initialize()
{
	mModelMatrix = Matrix::Identity;
	mIsFreezed = false;
	SAFE_RELEASE(mEffect);
	SAFE_RELEASE(mMaterial);
	SAFE_RELEASE(mStateTreeNode);
	mDrawMode = GraphicsDrawMode::Triangles;
	mRecycleFrameCount = 0;

	return true;
}

bool IRenderBatch::Uninitialize()
{
	mModelMatrix = Matrix::Identity;
	mIsFreezed = false;
	SAFE_RELEASE(mEffect);
	SAFE_RELEASE(mMaterial);
	SAFE_RELEASE(mStateTreeNode);
	mDrawMode = GraphicsDrawMode::Triangles;
	mRecycleFrameCount = 0;

	return true;
}


void IRenderBatch::SetEffect(const IEffect* val)
{
	SAFE_ASSIGN_REF(mEffect, val);
}

void IRenderBatch::SetMaterial(const IMaterial* val)
{
	SAFE_ASSIGN_REF(mMaterial, val);
}

void IRenderBatch::SetStateTreeNode(RenderStateTreeLeafNode* val)
{
	SAFE_ASSIGN_REF(mStateTreeNode, val);
}

void IRenderBatch::CustomDraw(IRenderQueue& renderQueue, RenderingFlags renderingFlags /*= RenderingFlags::None*/)
{
	RETURN_IF_TRUE(IsEmpty());

	EffectTechnique* technique = mEffect->CurrentTechniqueGroup()->CurrentTechnique();
	EffectTechnique::PassCollectionType& renderPasses = technique->RenderPasses();
	RenderingStatics::Instance().CountRenderPass(renderPasses.Count());
	RenderingStatics::Instance().CountMaterial(mMaterial);
	RenderingStatics::Instance().CountMaterialTextures(mMaterial);

	FOR_EACH_COLLECTION(i, renderPasses)
	{
		IRenderPass* renderPass = *i;
		RenderingContext::Instance().ApplyRenderPass(renderPass);
		RenderingContext::Instance().ApplyMaterial(mMaterial);
		RenderingContext::Instance().ApplyState(mStateTreeNode);

		RenderingContext::Instance().ApplyBatch(this);
		RenderingContext::Instance().ValidateBeforeDraw();

		Draw(renderQueue, renderingFlags);
		RenderingContext::Instance().RestoreBatch();

		RenderingContext::Instance().RestoreState();
		RenderingContext::Instance().RestoreMaterial();
		RenderingContext::Instance().RestoreRenderPass();
	}


	
}



MEDUSA_END;