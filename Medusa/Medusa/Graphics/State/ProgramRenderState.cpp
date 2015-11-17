// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/ProgramRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;
ProgramRenderState::ProgramRenderState(uint program/*=0*/)
	:mProgram(program)
{
	
}

ProgramRenderState::~ProgramRenderState()
{

}

void ProgramRenderState::Apply()const
{
	Render::Instance().UseProgram(mProgram);
}

ProgramRenderState* ProgramRenderState::Clone() const
{
	ProgramRenderState* state=new ProgramRenderState();
	state->SetProgram(mProgram);
	return state;
}

bool ProgramRenderState::Equals( const IRenderState& state ) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const ProgramRenderState& val=(const ProgramRenderState&)state;

	return mProgram==val.Program();
}

ProgramRenderState* ProgramRenderState::Current()
{
	IRender& render=Render::Instance();
	return new ProgramRenderState(render.GetInteger(GraphicsIntegerName::CurrentProgram));
}



MEDUSA_IMPLEMENT_RTTI(ProgramRenderState,IRenderState);

MEDUSA_END;