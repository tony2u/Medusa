// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/RenderTarget/DefaultRenderTarget.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"
#include "Core/Profile/ProfileSample.h"
#include "Graphics/State/RenderTargetRenderState.h"
#include "Graphics/State/RenderStateMachine.h"

MEDUSA_BEGIN;

DefaultRenderTarget::DefaultRenderTarget(const FileIdRef& fileId)
	:IRenderTarget(fileId)
{
	mClearMask=GraphicsBufferComponentMask::All;
	mFrameBuffer=Render::Instance().GetInteger(GraphicsIntegerName::FrameBufferBinding);


}

DefaultRenderTarget::~DefaultRenderTarget()
{
}




MEDUSA_END;