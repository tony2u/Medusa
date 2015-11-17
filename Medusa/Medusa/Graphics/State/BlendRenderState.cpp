// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/BlendRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;
BlendRenderState::BlendRenderState(bool blendEnabled/*=false*/)
	:mEnabled(blendEnabled),
	mSrcRGBFunc(GraphicsBlendSrcFunc::SrcAlpha),
	mSrcAlphaFunc(GraphicsBlendSrcFunc::SrcAlpha),
	mDestRGBFunc(GraphicsBlendDestFunc::OneMinusSrcAlpha),
	mDestAlphaFunc(GraphicsBlendDestFunc::OneMinusSrcAlpha),
	mBlendRGBEquation(GraphicsBlendEquation::Add),
	mBlendAlphaEquation(GraphicsBlendEquation::Add),
	mBlendColor(Color4F::Zero)
{

}

BlendRenderState::~BlendRenderState()
{

}


void BlendRenderState::Apply()const
{
	Render::Instance().EnableFeature(GraphicsFeatures::Blend, mEnabled);
	if (mEnabled)
	{
		Render::Instance().SetBlendEquationSeparate(mBlendRGBEquation, mBlendAlphaEquation);
		Render::Instance().SetBlendFuncSeparate(mSrcRGBFunc, mSrcAlphaFunc, mDestRGBFunc, mDestAlphaFunc);
		Render::Instance().SetBlendColor(mBlendColor);
	}
}


BlendRenderState* BlendRenderState::Clone() const
{
	BlendRenderState* state = new BlendRenderState();
	state->Enable(mEnabled);
	state->SetBlendAlphaEquation(mBlendAlphaEquation);
	state->SetBlendColor(mBlendColor);
	state->SetBlendRGBEquation(mBlendRGBEquation);
	state->SetDestAlphaFunc(mDestAlphaFunc);
	state->SetDestRGBFunc(mDestRGBFunc);
	state->SetSrcAlphaFunc(mSrcAlphaFunc);
	state->SetSrcRGBFunc(mSrcRGBFunc);
	return state;
}

bool BlendRenderState::Equals(const IRenderState& state) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const BlendRenderState& val = (const BlendRenderState&)state;

	return mEnabled == val.IsEnabled() &&
		mBlendAlphaEquation == val.BlendAlphaEquation() &&
		mBlendColor == val.BlendColor() &&
		mBlendRGBEquation == val.BlendRGBEquation() &&
		mDestAlphaFunc == val.DestAlphaFunc() &&
		mDestRGBFunc == val.DestRGBFunc() &&
		mSrcAlphaFunc == val.SrcAlphaFunc() &&
		mSrcRGBFunc == val.SrcRGBFunc();
}

BlendRenderState* BlendRenderState::Current()
{
	IRender& render = Render::Instance();

	BlendRenderState* blendState = new BlendRenderState();
	blendState->Enable(render.IsFeatureEnabled(GraphicsFeatures::Blend));
	blendState->SetSrcRGBFunc((GraphicsBlendSrcFunc)render.GetInteger(GraphicsIntegerName::BlendSrcRGBFunc));
	blendState->SetSrcAlphaFunc((GraphicsBlendSrcFunc)render.GetInteger(GraphicsIntegerName::BlendSrcAlphaFunc));
	blendState->SetDestRGBFunc((GraphicsBlendDestFunc)render.GetInteger(GraphicsIntegerName::BlendDestRGBFunc));
	blendState->SetDestAlphaFunc((GraphicsBlendDestFunc)render.GetInteger(GraphicsIntegerName::BlendDestAlphaFunc));
	blendState->SetBlendRGBEquation((GraphicsBlendEquation)render.GetInteger(GraphicsIntegerName::BlendRGBEquation));
	blendState->SetBlendAlphaEquation((GraphicsBlendEquation)render.GetInteger(GraphicsIntegerName::BlendAlphaEquation));
	Color4F originalColor;
	render.GetFloatArray(GraphicsFloatArrayName::BlendColor, originalColor.Buffer);
	blendState->SetBlendColor(originalColor);

	return blendState;

}

BlendRenderState* BlendRenderState::Default()
{
	IRender& render = Render::Instance();

	BlendRenderState* blendState = new BlendRenderState();
	blendState->Enable(render.IsFeatureEnabled(GraphicsFeatures::Blend));

	return blendState;
}


bool BlendRenderState::Enable(bool val)
{
	RETURN_FALSE_IF_EQUAL(mEnabled, val);
	mEnabled = val;
	OnStateChanged();
	return true;
}

bool BlendRenderState::SetSrcRGBFunc(GraphicsBlendSrcFunc val)
{
	RETURN_FALSE_IF_EQUAL(mSrcRGBFunc, val);
	mSrcRGBFunc = val; 
	OnStateChanged();
	return true;

}

bool BlendRenderState::SetSrcAlphaFunc(GraphicsBlendSrcFunc val)
{
	RETURN_FALSE_IF_EQUAL(mSrcAlphaFunc, val);

	mSrcAlphaFunc = val; 
	OnStateChanged();
	return true;

}

bool BlendRenderState::SetDestRGBFunc(GraphicsBlendDestFunc val)
{
	RETURN_FALSE_IF_EQUAL(mDestRGBFunc, val);

	mDestRGBFunc = val; 
	OnStateChanged();
	return true;

}

bool BlendRenderState::SetDestAlphaFunc(GraphicsBlendDestFunc val)
{
	RETURN_FALSE_IF_EQUAL(mDestAlphaFunc, val);

	mDestAlphaFunc = val; 
	OnStateChanged();
	return true;

}

bool BlendRenderState::SetBlendRGBEquation(GraphicsBlendEquation val)
{
	RETURN_FALSE_IF_EQUAL(mBlendRGBEquation, val);

	mBlendRGBEquation = val; 
	OnStateChanged();
	return true;

}

bool BlendRenderState::SetBlendAlphaEquation(GraphicsBlendEquation val)
{
	RETURN_FALSE_IF_EQUAL(mBlendAlphaEquation, val);

	mBlendAlphaEquation = val; 
	OnStateChanged();
	return true;

}

bool BlendRenderState::SetBlendColor(const Color4F& val)
{
	RETURN_FALSE_IF_EQUAL(mBlendColor, val);

	mBlendColor = val; 
	OnStateChanged();
	return true;

}


bool BlendRenderState::SetBlendFunc(GraphicsBlendSrcFunc srcFunc, GraphicsBlendDestFunc destFunc)
{
	if (mSrcAlphaFunc == srcFunc&&mSrcRGBFunc == srcFunc&&
		mDestAlphaFunc == destFunc&&mDestRGBFunc == destFunc)
	{
		return false;
	}

	mSrcAlphaFunc = mSrcRGBFunc = srcFunc;
	mDestAlphaFunc = mDestRGBFunc = destFunc;
	OnStateChanged();
	return true;

}

intp BlendRenderState::HashCode() const
{
	if (mEnabled)
	{
		return (intp)mSrcRGBFunc ^
			(intp)mSrcAlphaFunc^
			(intp)mDestRGBFunc^
			(intp)mDestAlphaFunc^
			(intp)mBlendRGBEquation.ToInt()^
			(intp)mBlendAlphaEquation.ToInt()^
			(intp)mBlendColor.HashCode();
	}
	return 0;
}

MEDUSA_IMPLEMENT_RTTI(BlendRenderState, IRenderState);


MEDUSA_END;