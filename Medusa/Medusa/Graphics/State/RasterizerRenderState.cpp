// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/RasterizerRenderState.h"
#include "Graphics/Render/Render.h"
#include "Resource/Effect/Shader/Parameter/ShaderUniform.h"
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

Share<RasterizerRenderState> RasterizerRenderState::Clone() const
{
	Share<RasterizerRenderState> state = new RasterizerRenderState();
	state->CopyFrom(*this);
	return state;
}

void RasterizerRenderState::CopyFrom(const IRenderState& other)
{
	MEDUSA_ASSERT(other.Type() == Type(), "Cannot copy render state with different type");
	RasterizerRenderState& val = (RasterizerRenderState&)other;
	mCullMode = val.mCullMode;
	mFrontFace = val.mFrontFace;
	mCullFaceEnabled = val.mCullFaceEnabled;
	mColorMask = val.mColorMask;
}

bool RasterizerRenderState::Equals(const IRenderState& state) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const RasterizerRenderState& val=(const RasterizerRenderState&)state;
	return mCullFaceEnabled==val.IsEnabled()&&
		mCullMode==val.CullMode()&&
		mFrontFace==val.FrontFace()&&
		mColorMask==val.ColorMask();
}

Share<RasterizerRenderState> RasterizerRenderState::Current()
{
	IRender& render=Render::Instance();
	Share<RasterizerRenderState> state=new RasterizerRenderState();

	state->Enable(render.GetBoolean(GraphicsBooleanName::CullFace));
	state->SetCullMode(GraphicsFace(render.GetInteger(GraphicsIntegerName::CullFaceMode)));
	state->SetFrontFace(GraphicsFrontFace(render.GetInteger(GraphicsIntegerName::FrontFace)));

	Array<bool,4> colorMask;
	render.GetBooleanArray(GraphicsBooleanArrayName::ColorWriteMask, colorMask.MutableItems());

	GraphicsColorMask resultColorMask;

	MEDUSA_FLAG_ENABLE(resultColorMask,GraphicsColorMask::R,colorMask[0]);
	MEDUSA_FLAG_ENABLE(resultColorMask,GraphicsColorMask::G,colorMask[1]);
	MEDUSA_FLAG_ENABLE(resultColorMask,GraphicsColorMask::B,colorMask[2]);
	MEDUSA_FLAG_ENABLE(resultColorMask,GraphicsColorMask::A,colorMask[3]);

	state->SetColorMask(resultColorMask);
	return state;
}


MEDUSA_END;