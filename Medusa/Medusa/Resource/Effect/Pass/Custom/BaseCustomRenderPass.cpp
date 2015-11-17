// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Pass/Custom/BaseCustomRenderPass.h"

MEDUSA_BEGIN;

BaseCustomRenderPass::BaseCustomRenderPass( const FileIdRef& fileId,int index/*=0*/)
	:IRenderPass(fileId,index)
{

}

BaseCustomRenderPass::~BaseCustomRenderPass()
{
	Uninitialize();
}

void BaseCustomRenderPass::UpdateShaderVariables( RenderingStep step )
{

}

void BaseCustomRenderPass::Validate()
{

}

void BaseCustomRenderPass::Invalidate()
{

}



MEDUSA_END;