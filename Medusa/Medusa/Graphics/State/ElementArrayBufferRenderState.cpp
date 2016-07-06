// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/ElementArrayBufferRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;

ElementArrayBufferRenderState::ElementArrayBufferRenderState(uint buffer/*=0*/)
	:BaseBufferRenderState(buffer)
{
	
}

ElementArrayBufferRenderState::~ElementArrayBufferRenderState()
{

}

void ElementArrayBufferRenderState::Apply()const
{
	Render::Instance().BindBuffer(GraphicsBufferType::Elements,mBuffer);
}


Share<ElementArrayBufferRenderState> ElementArrayBufferRenderState::Current()
{
	return new ElementArrayBufferRenderState(Render::Instance().GetInteger(GraphicsIntegerName::ElementArrayBufferBinding));
}

Share<ElementArrayBufferRenderState> ElementArrayBufferRenderState::Clone() const
{
	return new ElementArrayBufferRenderState(mBuffer);
}

void ElementArrayBufferRenderState::CopyFrom(const IRenderState& other)
{
	MEDUSA_ASSERT(other.Type() == Type(), "Cannot copy render state with different type");
	ElementArrayBufferRenderState& val = (ElementArrayBufferRenderState&)other;
	mBuffer = val.mBuffer;
}


MEDUSA_END;