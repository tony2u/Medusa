// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/RenderTarget/CustomRenderTarget.h"
#include "Graphics/Render/Render.h"
#include "Graphics/Buffer/FrameBuffer.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Graphics/State/RenderTargetRenderState.h"

MEDUSA_BEGIN;

CustomRenderTarget::CustomRenderTarget(const FileIdRef& fileId):IRenderTarget(fileId),mZOrder(1)
{
	Generate();
}

CustomRenderTarget::~CustomRenderTarget()
{

}

MEDUSA_END;