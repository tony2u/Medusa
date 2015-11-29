// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/DepthStencilRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;
DepthStencilRenderState::DepthStencilRenderState()
{

}

DepthStencilRenderState::~DepthStencilRenderState()
{

}

void DepthStencilRenderState::Apply()const
{
	IRender& render= Render::Instance();
	render.EnableFeature(GraphicsFeatures::DepthTest,mDepthTestEnabled);
	render.EnableDepthWrite(mDepthWritable);
	render.SetDepthFunc(mDepthFunc);
	render.SetClearDepth(mDepthClearValue);

	render.EnableFeature(GraphicsFeatures::StencilTest,mStencilTestEnabled);
	render.SetStencilClearValue(mStencilClearValue);

	render.SetStencilFuncSeparate(GraphicsFace::Front,mFrontStencilFunc,mFrontRefValue,mFrontReadMask);
	render.SetStencilWriteMaskSeparate(GraphicsFace::Front,mFrontWriteMask);
	render.SetStencilOperationSeparate(GraphicsFace::Front,mFrontStencilFailOp,mFrontStencilDepthFailOp,mFrontStencilPassOp);

	render.SetStencilFuncSeparate(GraphicsFace::Back,mBackStencilFunc,mBackRefValue,mBackReadMask);
	render.SetStencilWriteMaskSeparate(GraphicsFace::Back,mBackWriteMask);
	render.SetStencilOperationSeparate(GraphicsFace::Back,mBackStencilFailOp,mBackStencilDepthFailOp,mBackStencilPassOp);
}

DepthStencilRenderState* DepthStencilRenderState::Clone() const
{
	DepthStencilRenderState* state=new DepthStencilRenderState();
	state->CopyFrom(*this);
	return state;
}

void DepthStencilRenderState::CopyFrom(const IRenderState& other)
{
	MEDUSA_ASSERT(other.Type() == Type(), "Cannot copy render state with different type");
	DepthStencilRenderState& val = (DepthStencilRenderState&)other;

	mDepthTestEnabled = val.mDepthTestEnabled;
	mDepthWritable = val.mDepthWritable;
	mDepthFunc = val.mDepthFunc;
	mDepthClearValue = val.mDepthClearValue;

	mStencilTestEnabled = val.mStencilTestEnabled;
	mStencilClearValue = val.mStencilClearValue;

	mFrontStencilDepthFailOp = val.mFrontStencilDepthFailOp;
	mFrontStencilFailOp = val.mFrontStencilFailOp;
	mFrontStencilFunc = val.mFrontStencilFunc;
	mFrontStencilPassOp = val.mFrontStencilPassOp;
	mFrontReadMask = val.mFrontReadMask;
	mFrontWriteMask = val.mFrontWriteMask;
	mFrontRefValue = val.mFrontRefValue;

	mBackStencilDepthFailOp = val.mBackStencilDepthFailOp;
	mBackStencilFailOp = val.mBackStencilFailOp;
	mBackStencilFunc = val.mBackStencilFunc;
	mBackStencilPassOp = val.mBackStencilPassOp;
	mBackReadMask = val.mBackReadMask;
	mBackWriteMask = val.mBackWriteMask;
	mBackRefValue = val.mBackRefValue;

}

bool DepthStencilRenderState::Equals(const IRenderState& state) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const DepthStencilRenderState& val=(const DepthStencilRenderState&)state;

	return mDepthTestEnabled==val.IsDepthTestEnabled()&&
		mDepthWritable==val.IsDepthWriteEnabled()&&
		mDepthFunc==val.DepthFunc()&&
		Math::IsEqual(mDepthClearValue,val.DepthClearValue())&&
		mStencilTestEnabled==val.IsStencilTestEnabled()&&
		mStencilClearValue==val.StencilClearValue()&&
		mFrontStencilDepthFailOp==val.FrontStencilDepthFailOp()&&
		mFrontStencilFailOp==val.FrontStencilFailOp()&&
		mFrontStencilFunc==val.FrontStencilFunc()&&
		mFrontStencilPassOp==val.FrontStencilPassOp()&&
		mFrontRefValue==val.FrontRefValue()&&
		mFrontReadMask==val.FrontReadMask()&&
		mFrontWriteMask==val.FrontWriteMask()&&
		mBackStencilDepthFailOp==val.BackStencilDepthFailOp()&&
		mBackStencilFailOp==val.BackStencilFailOp()&&
		mBackStencilFunc==val.BackStencilFunc()&&
		mBackStencilPassOp==val.BackStencilPassOp()&&
		mBackRefValue==val.BackRefValue()&&
		mBackReadMask==val.BackReadMask()&&
		mBackWriteMask==val.BackWriteMask();


}

DepthStencilRenderState* DepthStencilRenderState::Current()
{
	IRender& render=Render::Instance();

	DepthStencilRenderState* depthState=new DepthStencilRenderState();
	depthState->EnableDepthTest(render.IsFeatureEnabled(GraphicsFeatures::DepthTest));
	depthState->EnableDepthWrite(render.GetBoolean(GraphicsBooleanName::DepthWritable));
	depthState->SetDepthFunc((GraphicsFuncType)render.GetInteger(GraphicsIntegerName::DepthFunc));
	depthState->SetDepthClearValue(render.GetFloat(GraphicsFloatName::DepthClearValue));

	depthState->EnableStencilTest(render.IsFeatureEnabled(GraphicsFeatures::StencilTest));
	depthState->SetStencilClearValue(render.GetInteger(GraphicsIntegerName::StencilClearValue));

	depthState->SetFrontReadMask(render.GetInteger(GraphicsIntegerName::StencilValueMask));
	depthState->SetFrontRefValue(render.GetInteger(GraphicsIntegerName::StencilRefValue));
	depthState->SetFrontWriteMask(render.GetInteger(GraphicsIntegerName::StencilWriteMask));
	depthState->SetFrontStencilDepthFailOp((GraphicsStencilOperation)render.GetInteger(GraphicsIntegerName::StencilPassDepthFailOperation));
	depthState->SetFrontStencilFailOp((GraphicsStencilOperation)render.GetInteger(GraphicsIntegerName::StencilFailOperation));
	depthState->SetFrontStencilPassOp((GraphicsStencilOperation)render.GetInteger(GraphicsIntegerName::StencilPassDepthPassOperation));
	depthState->SetFrontStencilFunc((GraphicsFuncType)render.GetInteger(GraphicsIntegerName::StencilFunc));

	depthState->SetBackReadMask(render.GetInteger(GraphicsIntegerName::StencilBackValueMask));
	depthState->SetBackRefValue(render.GetInteger(GraphicsIntegerName::StencilBackRefValue));
	depthState->SetBackWriteMask(render.GetInteger(GraphicsIntegerName::StencilBackWriteMask));
	depthState->SetBackStencilDepthFailOp((GraphicsStencilOperation)render.GetInteger(GraphicsIntegerName::StencilBackPassDepthFailOperation));
	depthState->SetBackStencilFailOp((GraphicsStencilOperation)render.GetInteger(GraphicsIntegerName::StencilBackFailOperation));
	depthState->SetBackStencilPassOp((GraphicsStencilOperation)render.GetInteger(GraphicsIntegerName::StencilBackPassDepthPassOperation));
	depthState->SetBackStencilFunc((GraphicsFuncType)render.GetInteger(GraphicsIntegerName::StencilBackFunc));

	return depthState;
}



MEDUSA_IMPLEMENT_RTTI(DepthStencilRenderState,IRenderState);


MEDUSA_END;