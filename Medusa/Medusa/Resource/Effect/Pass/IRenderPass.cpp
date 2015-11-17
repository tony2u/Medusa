// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Pass/IRenderPass.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Rendering/RenderingContext.h"
#include "Rendering/IDrawable.h"

MEDUSA_BEGIN;

IRenderPass::IRenderPass(const FileIdRef& fileId/*=FileId::Empty*/, uint index/*=0*/)
	:IResource(fileId),mIndex(index)
{
	mTechnique=nullptr;
	
}

IRenderPass::~IRenderPass()
{
}


void IRenderPass::Apply()
{
	RenderStateSet::Apply();
}

void IRenderPass::Restore()
{
	RenderStateSet::Restore();
}

const StringRef IRenderPass::DefaultRenderPassName="P0";

MEDUSA_END;