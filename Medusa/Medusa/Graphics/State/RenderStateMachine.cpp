// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/Render/Render.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Core/Log/Log.h"

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
#include "Graphics/State/ShaderUniformRenderState.h"


MEDUSA_BEGIN;

RenderStateMachine::RenderStateMachine()
{
}

RenderStateMachine::~RenderStateMachine()
{
	for(auto i:mRenderStates)
	{
		RenderStateStack* stack=i.Value;
		stack->Clear();
		SAFE_DELETE(stack);
	}
}

bool RenderStateMachine::Initialize()
{
	mRenderStates.Add((uint)BlendRenderState::GetTypeIdStatic(),RenderStateStack::New(BlendRenderState::Current()));
	mRenderStates.Add((uint)DepthStencilRenderState::GetTypeIdStatic(),RenderStateStack::New(DepthStencilRenderState::Current()));
	mRenderStates.Add((uint)ArrayBufferRenderState::GetTypeIdStatic(), RenderStateStack::New(ArrayBufferRenderState::Current()));
	mRenderStates.Add((uint)ElementArrayBufferRenderState::GetTypeIdStatic(),RenderStateStack::New(ElementArrayBufferRenderState::Current()));
	mRenderStates.Add((uint)FeatureRenderState::GetTypeIdStatic(),RenderStateStack::New(FeatureRenderState::Current()));
	mRenderStates.Add((uint)PixelStoreRenderState::GetTypeIdStatic(),RenderStateStack::New(PixelStoreRenderState::Current()));
	mRenderStates.Add((uint)ProgramRenderState::GetTypeIdStatic(),RenderStateStack::New(ProgramRenderState::Current()));
	mRenderStates.Add((uint)RasterizerRenderState::GetTypeIdStatic(),RenderStateStack::New(RasterizerRenderState::Current()));
	mRenderStates.Add((uint)RenderTargetRenderState::GetTypeIdStatic(),RenderStateStack::New(RenderTargetRenderState::Current(true)));
	mRenderStates.Add((uint)ScissorRenderState::GetTypeIdStatic(),RenderStateStack::New(ScissorRenderState::Current()));
	mRenderStates.Add((uint)SamplerRenderState::GetTypeIdStatic(), RenderStateStack::New(SamplerRenderState::Current()));
	mRenderStates.Add((uint)ShaderUniformRenderState::GetTypeIdStatic(), new RenderStateStack());


	/*FOR_EACH_COLLECTION(i,mRenderStates)
	{
		RenderStateStack* stack=i->Value;
		auto state=stack->Top();
		state->Retain();
	}*/
	
	return true;

}

void RenderStateMachine::Push(const Share<IRenderState>& state )
{
	RenderStateStack* stack = mRenderStates[(uint)state->Type()];

#ifdef MEDUSA_SAFE_CHECK
	if (stack==nullptr)
	{
		Log::AssertFailedFormat("Empty state stack when pushing {} [{}]:",state->Class().Name().c_str(),state->Type());
		return;
	}
#endif

#ifdef MEDUSA_SAFE_CHECK
	auto currentVal = stack->TopOr(nullptr);
	if (currentVal==nullptr||!state->Equals(*currentVal))
	{
		state->Apply();
	}
	else
	{
		//duplicate state push
	}
#else

	state->Apply();

#endif
	

	stack->Push(state);
}


void RenderStateMachine::Pop( const Share<IRenderState>& state /*=nullptr*/)
{
	RenderStateStack* stack=mRenderStates[(uint)state->Type()];
#ifdef MEDUSA_SAFE_CHECK
	if (stack==nullptr)
	{
		Log::AssertFailedFormat("Empty state stack when popping {} [{}]:", state->Class().Name().c_str(), state->Type());
		return;
	}
#endif

	Share<IRenderState> currentVal=stack->PopCopy();

#ifdef MEDUSA_SAFE_CHECK
	if (state!=nullptr&&currentVal!=state)
	{
		Log::FormatError("Not pop the SAME render state.Forget to pop after push?");
		return;
	}

	/*if (stack->IsEmpty())
	{
		Log::AssertFailedFormat("Empty state stack after popping {} [{}]:", state->Class().Name().c_str(), state->Type());
		return;
	}*/
#endif
	Share<IRenderState> prevVal = stack->TopOr(nullptr);

#ifdef MEDUSA_SAFE_CHECK
	if (prevVal!=nullptr&&!currentVal->Equals(*prevVal))
	{
		prevVal->Apply();
	}
	else
	{
		//duplicate state pop
	}
#else
	if (prevVal!=nullptr)
	{
		prevVal->Apply();
	}
#endif
}



MEDUSA_END;
