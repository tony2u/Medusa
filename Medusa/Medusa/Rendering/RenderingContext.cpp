// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/RenderingContext.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"

#include "Resource/Material/IMaterial.h"
#include "Resource/Model/IModel.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Camera/Camera.h"
#include "Graphics/State/Tree/RenderStateTreeLeafNode.h"


MEDUSA_BEGIN;

RenderingContext::RenderingContext()
{
	mStep=RenderingStep::RenderTarget;

	mRenderTarget=nullptr;
	mCamera=nullptr;
	mRenderPass=nullptr;
	mMaterial=nullptr;
	mBatch=nullptr;
	mEffect=nullptr;
	mStateNode=nullptr;
	mDrawMode = GraphicsDrawMode::Triangles;
}

RenderingContext::~RenderingContext()
{
	SAFE_RELEASE(mRenderTarget);
	SAFE_RELEASE(mCamera);

	SAFE_RELEASE(mRenderPass);
	SAFE_RELEASE(mMaterial);
	SAFE_RELEASE(mEffect);

	mBatch=nullptr;
	mStateNode=nullptr;

}

void RenderingContext::ApplyRenderTargetAndCamera( IRenderTarget* val ,Camera* camera)
{
	SetRenderTargetAndCamera(val,camera);
	if (mRenderTarget!=nullptr)
	{
		mRenderTarget->Apply();
	}
}


void RenderingContext::ApplyRenderPass( IRenderPass* val )
{
	SetRenderPass(val);
	
	if (mRenderPass!=nullptr)
	{
		mRenderPass->Invalidate();
		mRenderPass->Apply();
		UpdateShaderUniforms();
	}
}

void RenderingContext::ApplyMaterial(const  IMaterial* val )
{
	SetMaterial(val);

	if (mMaterial!=nullptr)
	{
		mMaterial->Apply();
		UpdateShaderUniforms();
	}
}


void RenderingContext::ApplyState(RenderStateTreeLeafNode* stateNode)
{
	SetState(stateNode);
	stateNode->Apply();
	UpdateShaderUniforms();
}


void RenderingContext::ApplyDrawMode(GraphicsDrawMode val)
{
	SetDrawMode(val);
	UpdateShaderUniforms();

}

void RenderingContext::ApplyBatch( IRenderBatch* val )
{
	SetBatch(val);
	if (mBatch!=nullptr)
	{
		mBatch->Apply();
		UpdateShaderUniforms();
	}
}


void RenderingContext::RestoreRenderTargetAndCamera()
{
	if (mRenderTarget!=nullptr)
	{
		mRenderTarget->Restore();
	}

	ResetRenderTargetAndCamera();
}

void RenderingContext::RestoreRenderPass()
{
	if (mRenderPass!=nullptr)
	{
		mRenderPass->Restore();
	}
	ResetRenderPass();
}


void RenderingContext::RestoreMaterial()
{
	if (mMaterial!=nullptr)
	{
		mMaterial->Restore();
	}

	ResetMaterial();
}


void RenderingContext::RestoreState()
{
	if (mStateNode!=nullptr)
	{
		mStateNode->Restore();
	}
	ResetState();
	
}

void RenderingContext::RestoreDrawMode()
{
	ResetDrawMode();
}

void RenderingContext::RestoreBatch()
{
	if (mBatch!=nullptr)
	{
		mBatch->Restore();
	}
	ResetBatch();
}

void RenderingContext::ValidateBeforeDraw()
{
	if (mRenderPass!=nullptr)
	{
		mRenderPass->Validate();
	}
}

void RenderingContext::UpdateShaderUniforms()
{
	if (mRenderPass!=nullptr)
	{
		mRenderPass->UpdateShaderUniforms(mStep);
	}
}

void RenderingContext::SetRenderTargetAndCamera( IRenderTarget* val ,Camera* camera)
{
	mStep=RenderingStep::RenderTarget;
	SAFE_ASSIGN_REF(mRenderTarget,val);
	SAFE_ASSIGN_REF(mCamera,camera);

}

void RenderingContext::SetRenderPass( IRenderPass* val )
{
	mStep=RenderingStep::RenderPass;
	SAFE_ASSIGN_REF(mRenderPass,val);
}

void RenderingContext::SetMaterial(const  IMaterial* val )
{
	mStep=RenderingStep::Material;
	SAFE_ASSIGN_REF(mMaterial,val);
}


void RenderingContext::SetState(RenderStateTreeLeafNode* stateNode)
{
	mStep=RenderingStep::State;
	SAFE_ASSIGN_REF(mStateNode, stateNode);
	mStateNode = stateNode;
}


void RenderingContext::SetBatch( IRenderBatch* val )
{
	mStep=RenderingStep::Batch;
	mBatch = val;
}

void RenderingContext::SetEffect(const IEffect* val )
{
	SAFE_ASSIGN_REF(mEffect,val);
}

void RenderingContext::SetDrawMode(GraphicsDrawMode val)
{
	mStep = RenderingStep::DrawMode;
	mDrawMode = val;
}


void RenderingContext::ResetRenderTargetAndCamera()
{
	mStep=RenderingStep::RenderTarget;
	SAFE_RELEASE(mRenderTarget);
	SAFE_RELEASE(mCamera);
}

void RenderingContext::ResetRenderPass()
{
	mStep=RenderingStep::RenderTarget;
	SAFE_RELEASE(mRenderPass);
}

void RenderingContext::ResetMaterial()
{
	mStep=RenderingStep::RenderPass;
	SAFE_RELEASE(mMaterial);
}

void RenderingContext::ResetBatch()
{
	mStep=RenderingStep::State;
	mBatch=nullptr;
}
void RenderingContext::ResetState()
{
	mStep=RenderingStep::Material;
	mStateNode=nullptr;
}

void RenderingContext::ResetEffect()
{
	SAFE_RELEASE(mEffect);
}

void RenderingContext::ResetDrawMode()
{
	mStep = RenderingStep::DrawMode;
	mDrawMode = GraphicsDrawMode::Triangles;
}



MEDUSA_END;