// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/RasterizerRenderState.h"
#include "Graphics/Render/Render.h"
#include "Resource/Effect/Shader/Parameter/ShaderConstant.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/ResourceNames.h"

MEDUSA_BEGIN;

RasterizerRenderState::RasterizerRenderState( )
{

}

RasterizerRenderState::~RasterizerRenderState()
{

}

void RasterizerRenderState::Apply()const
{
	Render::Instance().EnableFeature(GraphicsFeatures::CullFace,mCullFaceEnabled);
	Render::Instance().CullFace(mCullMode);
	Render::Instance().SetFrontFace(mFrontFace);

	Render::Instance().SetColorMask(mColorMask);
}

RasterizerRenderState* RasterizerRenderState::Clone() const
{
	RasterizerRenderState* state=new RasterizerRenderState();
	state->SetCullMode(mCullMode);
	state->SetFrontFace(mFrontFace);
	state->EnableCullFace(mCullFaceEnabled);
	state->SetColorMask(mColorMask);
	return state;
}

bool RasterizerRenderState::Equals( const IRenderState& state ) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const RasterizerRenderState& val=(const RasterizerRenderState&)state;
	return mCullFaceEnabled==val.IsCullFaceEnabled()&&
		mCullMode==val.CullMode()&&
		mFrontFace==val.FrontFace()&&
		mColorMask==val.ColorMask();
}

RasterizerRenderState* RasterizerRenderState::Current()
{
	IRender& render=Render::Instance();
	RasterizerRenderState* state=new RasterizerRenderState();

	state->EnableCullFace(render.GetBoolean(GraphicsBooleanName::CullFace));
	state->SetCullMode(GraphicsFace(render.GetInteger(GraphicsIntegerName::CullFaceMode)));
	state->SetFrontFace(GraphicsFrontFace(render.GetInteger(GraphicsIntegerName::FrontFace)));

	Array<bool,4> colorMask;
	render.GetBooleanArray(GraphicsBooleanArrayName::ColorWriteMask, colorMask.MutableItems());

	GraphicsColorMask resultColorMask;
	resultColorMask.SetOrRemoveIf(GraphicsColorMask::R,colorMask[0]);
	resultColorMask.SetOrRemoveIf(GraphicsColorMask::G,colorMask[1]);
	resultColorMask.SetOrRemoveIf(GraphicsColorMask::B,colorMask[2]);
	resultColorMask.SetOrRemoveIf(GraphicsColorMask::A,colorMask[3]);

	state->SetColorMask(resultColorMask);
	return state;
}


MEDUSA_IMPLEMENT_RTTI(RasterizerRenderState,IRenderState);
MEDUSA_END;