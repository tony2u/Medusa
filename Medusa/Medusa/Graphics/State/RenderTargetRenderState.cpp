// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/RenderTargetRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;
RenderTargetRenderState::RenderTargetRenderState(uint frameBuffer,const Rect2I& viewPort,const Color4F& clearColor,bool isDefault/*=false*/)
	:mFrameBuffer(frameBuffer),mViewPort(viewPort),mClearColor(clearColor),mIsDefault(isDefault)
{
	
}

RenderTargetRenderState::RenderTargetRenderState()
	:mFrameBuffer(0),mViewPort(Rect2I::Zero),mClearColor(Color4F::Black)
{

}

RenderTargetRenderState::~RenderTargetRenderState()
{

}

void RenderTargetRenderState::Apply()const
{
	RETURN_IF_TRUE(mIsDefault);
	Render::Instance().BindFrameBuffer(mFrameBuffer);
	Render::Instance().SetViewPort(mViewPort);
	Render::Instance().SetClearColor(mClearColor);


}

RenderTargetRenderState* RenderTargetRenderState::Clone() const
{
	RenderTargetRenderState* state=new RenderTargetRenderState();
	state->CopyFrom(*this);
	return state;
}

void RenderTargetRenderState::CopyFrom(const IRenderState& other)
{
	MEDUSA_ASSERT(other.Type() == Type(), "Cannot copy render state with different type");
	RenderTargetRenderState& val = (RenderTargetRenderState&)other;
	mFrameBuffer = val.mFrameBuffer;
	mViewPort = val.mViewPort;
	mClearColor = val.mClearColor;

}

bool RenderTargetRenderState::Equals(const IRenderState& state) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	RETURN_TRUE_IF_TRUE(mIsDefault);
	const RenderTargetRenderState& val=(const RenderTargetRenderState&)state;

	return mFrameBuffer==val.FrameBuffer()&&
		mViewPort==val.ViewPort()&&
		mClearColor==val.ClearColor();
}

RenderTargetRenderState* RenderTargetRenderState::Current(bool isDefault/*=false*/)
{
	IRender& render=Render::Instance();

	uint frameBuffer=render.GetInteger(GraphicsIntegerName::FrameBufferBinding);
	Rect2I viewPort;
	render.GetIntegerArray(GraphicsIntegerArrayName::Viewport,viewPort.GetBuffer());

	Color4F clearColor;
	render.GetFloatArray(GraphicsFloatArrayName::ClearColor,clearColor.Buffer);
	return new RenderTargetRenderState(frameBuffer,viewPort,clearColor,isDefault);
}


MEDUSA_IMPLEMENT_RTTI(RenderTargetRenderState,IRenderState);

MEDUSA_END;