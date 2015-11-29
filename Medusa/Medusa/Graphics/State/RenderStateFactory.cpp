// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/RenderStateFactory.h"

#include "Graphics/State/ArrayBufferRenderState.h"
#include "Graphics/State/BlendRenderState.h"
#include "Graphics/State/DepthStencilRenderState.h"
#include "Graphics/State/ElementArrayBufferRenderState.h"
#include "Graphics/State/FeatureRenderState.h"
#include "Graphics/State/PixelStoreRenderState.h"
#include "Graphics/State/ProgramRenderState.h"
#include "Graphics/State/RasterizerRenderState.h"
#include "Graphics/State/RenderTargetRenderState.h"
#include "Graphics/State/SamplerRenderState.h"
#include "Graphics/State/ScissorRenderState.h"


MEDUSA_BEGIN;

RenderStateFactory::RenderStateFactory()
{
	Register<BlendRenderState>();
	Register<DepthStencilRenderState>();
	Register<ArrayBufferRenderState>();
	Register<ElementArrayBufferRenderState>();
	Register<FeatureRenderState>();
	Register<PixelStoreRenderState>();
	Register<ProgramRenderState>();
	Register<RasterizerRenderState>();
	Register<ScissorRenderState>();
	Register<SamplerRenderState>();
}

RenderStateFactory::~RenderStateFactory()
{
	
}


MEDUSA_END;
