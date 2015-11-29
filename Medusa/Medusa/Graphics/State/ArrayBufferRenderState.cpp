// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/ArrayBufferRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;

ArrayBufferRenderState::ArrayBufferRenderState(uint buffer/*=0*/)
	:BaseBufferRenderState(buffer)
{
	
}

ArrayBufferRenderState::~ArrayBufferRenderState()
{

}

void ArrayBufferRenderState::Apply()const
{
	Render::Instance().BindBuffer(GraphicsBufferType::Array,mBuffer);
}


ArrayBufferRenderState* ArrayBufferRenderState::Current()
{
	return new ArrayBufferRenderState(Render::Instance().GetInteger(GraphicsIntegerName::ArrayBufferBinding));
}

ArrayBufferRenderState* ArrayBufferRenderState::Clone() const
{
	ArrayBufferRenderState* state=new ArrayBufferRenderState(mBuffer);
	return state;
}

void ArrayBufferRenderState::CopyFrom(const IRenderState& other)
{
	MEDUSA_ASSERT(other.Type() == Type(), "Cannot copy render state with different type");
	ArrayBufferRenderState& val = (ArrayBufferRenderState&)other;
	mBuffer = val.mBuffer;
}

MEDUSA_IMPLEMENT_RTTI(ArrayBufferRenderState, BaseBufferRenderState);

MEDUSA_END;