// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/BaseBufferRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;

BaseBufferRenderState::BaseBufferRenderState(uint buffer/*=0*/)
	:mBuffer(buffer)
{
	
}

BaseBufferRenderState::~BaseBufferRenderState()
{

}

bool BaseBufferRenderState::Equals( const IRenderState& state ) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const BaseBufferRenderState& val=(const BaseBufferRenderState&)state;
	return mBuffer==val.Buffer();
}


MEDUSA_IMPLEMENT_RTTI(BaseBufferRenderState,IRenderState);

MEDUSA_END;