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
	mBatch=nullptr;
	mStateNode=nullptr;

}

void RenderingContext::ApplyRenderTargetAndCamera(const Share<IRenderTarget>& val , const Share<Camera>& camera)
{
	SetRenderTargetAndCamera(val,camera);
	if (mRenderTarget!=nullptr)
	{
		mRenderTarget->Apply();
	}
}


void RenderingContext::ApplyRenderPass(const Share<IRenderPass>& val )
{
	SetRenderPass(val);
	
	if (mRenderPass!=nullptr)
	{
		mRenderPass->Invalidate();
		mRenderPass->Apply();
		UpdateShaderUniforms();
	}
}

void RenderingContext::ApplyMaterial(const Share<IMaterial>& val )
{
	SetMaterial(val);

	if (mMaterial!=nullptr)
	{
		mMaterial->Apply();
		UpdateShaderUniforms();
	}
}


void RenderingContext::ApplyState(const Share<RenderStateTreeLeafNode>& stateNode)
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

void RenderingContext::SetRenderTargetAndCamera(const Share<IRenderTarget>& val , const Share<Camera>& camera)
{
	mStep=RenderingStep::RenderTarget;
	mRenderTarget = val;
	mCamera = camera;

}

void RenderingContext::SetRenderPass(const Share<IRenderPass>& val )
{
	mStep=RenderingStep::RenderPass;
	mRenderPass = val;
}

void RenderingContext::SetMaterial(const Share<IMaterial>& val )
{
	mStep=RenderingStep::Material;
	mMaterial = val;
}


void RenderingContext::SetState(const Share<RenderStateTreeLeafNode>& stateNode)
{
	mStep=RenderingStep::State;
	mStateNode = stateNode;
}


void RenderingContext::SetBatch( IRenderBatch* val )
{
	mStep=RenderingStep::Batch;
	mBatch = val;
}

void RenderingContext::SetEffect(const Share<IEffect>& val )
{
	mEffect = val;
}

void RenderingContext::SetDrawMode(GraphicsDrawMode val)
{
	mStep = RenderingStep::DrawMode;
	mDrawMode = val;
}


void RenderingContext::ResetRenderTargetAndCamera()
{
	mStep=RenderingStep::RenderTarget;
	mRenderTarget = nullptr;
	mCamera = nullptr;
}

void RenderingContext::ResetRenderPass()
{
	mStep=RenderingStep::RenderTarget;
	mRenderPass = nullptr;
}

void RenderingContext::ResetMaterial()
{
	mStep=RenderingStep::RenderPass;
	mMaterial = nullptr;
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
	mEffect = nullptr;
}

void RenderingContext::ResetDrawMode()
{
	mStep = RenderingStep::DrawMode;
	mDrawMode = GraphicsDrawMode::Triangles;
}



MEDUSA_END;