// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderStateSet.h"
#include "Core/Pattern/LazyStrongPtr.inl"

#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/IRenderState.h"
#include "Graphics/State/BlendRenderState.h"
#include "Graphics/State/ScissorRenderState.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Graphics/State/RenderStateFactory.h"
#include "Graphics/State/ShaderUniformRenderState.h"


MEDUSA_BEGIN;


RenderStateSet::RenderStateSet()
{
	mItems.SetAll(nullptr);
}


RenderStateSet::~RenderStateSet(void)
{
	mItems.Clear();
}


bool RenderStateSet::Equals(const RenderStateSet& states) const
{
	return false;
}

void RenderStateSet::Apply()const
{
	for (auto& state:mItems)
	{
		if (state!=nullptr)
		{
			RenderStateMachine::Instance().Push(state);
		}
	}
}


void RenderStateSet::Restore()const
{
	for (auto& state : mItems)
	{
		if (state != nullptr)
		{
			RenderStateMachine::Instance().Pop(state);
		}
	}
}

bool RenderStateSet::IsBlendEnabled() const
{
	auto state = GetState<BlendRenderState>();
	return state != nullptr&&state->IsEnabled();
}

void RenderStateSet::EnableBlend(bool val)
{
	auto state = AllocState<BlendRenderState>();
	state->Enable(val);
}

void RenderStateSet::SetBlendFunc(GraphicsBlendSrcFunc srcFunc, GraphicsBlendDestFunc destFunc)
{
	auto state = AllocState<BlendRenderState>();
	state->SetBlendFunc(srcFunc, destFunc);
}

Share<BlendRenderState> RenderStateSet::RemoveBlend()
{
	return RemoveState<BlendRenderState>();
}


bool RenderStateSet::HasScissorBox() const
{
	auto state = GetState<ScissorRenderState>();
	return state != nullptr;
}


bool RenderStateSet::IsScissorEnabled() const
{
	auto state = GetState<ScissorRenderState>();
	return state != nullptr&&state->IsEnabled();
}

void RenderStateSet::SetScissorBox(const Rect2F& val)
{
	auto state = AllocState<ScissorRenderState>();
	state->SetScissorBox(val);
}

void RenderStateSet::EnableScissor(bool val)
{
	auto state = AllocState<ScissorRenderState>();
	state->Enable(val);
}

Share<ScissorRenderState> RenderStateSet::RemoveScissor()
{
	return RemoveState<ScissorRenderState>();

}

const Rect2F* RenderStateSet::TryGetScissorBox() const
{
	auto state = GetState<ScissorRenderState>();
	RETURN_NULL_IF_NULL(state);
	return &state->ScissorBox();
}

const Rect2F& RenderStateSet::GetScissorBoxOrEmpty() const
{
	auto state = GetState<ScissorRenderState>();
	if (state != nullptr)
	{
		return state->ScissorBox();
	}
	return Rect2F::Zero;
}


ShaderUniformValue* RenderStateSet::FindOrCreateUniform(StringRef name)
{
	auto state = AllocState<ShaderUniformRenderState>();
	return state->FindOrCreate(name);
}

void RenderStateSet::UpdateFromParent(const RenderStateSet& selfRenderState, const RenderStateSet& parentRenderState, const Matrix4& selfWorldMatrix, RenderStateType flag)
{
	FOR_EACH_UINT32(i, (uint)RenderStateType::Count)
	{
		uint index = 1 << i;
		CONTINUE_IF_FALSE(MEDUSA_FLAG_HAS(flag, index));

		auto& state = mItems[i];
		auto& selfState = selfRenderState.mItems[i];
		auto& parentState = parentRenderState.mItems[i];

		if (selfState == nullptr&&parentState == nullptr)
		{
			if (state != nullptr)
			{
				state->Release();
				mItems[i] = nullptr;
			}
		}
		else
		{
			if (state == nullptr)
			{
				//do not add event listener
				state = RenderStateFactory::Instance().Create(i);
				mItems[i] = state;
			}
			state->UpdateWorldState(selfState, parentState, selfWorldMatrix);
		}

	}

	
}

void RenderStateSet::UpdateFromSelf(const RenderStateSet& selfRenderState, const Matrix4& selfWorldMatrix, RenderStateType flag)
{
	FOR_EACH_UINT32(i, (uint)RenderStateType::Count)
	{
		uint index = 1 << i;
		CONTINUE_IF_FALSE(MEDUSA_FLAG_HAS(flag, index));
		
		auto& state = mItems[i];
		auto& selfState = selfRenderState.mItems[i];

		if (selfState!=nullptr)
		{
			if (state == nullptr)
			{
				//do not add event listener
				state = RenderStateFactory::Instance().Create(i);
				mItems[i] = state;
			}
			state->UpdateWorldState(selfState,nullptr,selfWorldMatrix);
		}
		else
		{
			if (state!= nullptr)
			{
				state->Release();
				mItems[i] = nullptr;
			}
		}
	}
}

void RenderStateSet::OnStateChangedEvent(IRenderState& state)
{
	OnStateChanged(state);
}

Share<IRenderState> RenderStateSet::GetState(RenderStateType type) const
{
	uint32 index = Math::CountTrailingZero((uint32)type);
	return mItems[index];
}

Share<IRenderState> RenderStateSet::AllocState(RenderStateType type)
{
	uint32 index = Math::CountTrailingZero((uint32)type);
	auto& state = mItems[index];
	if (state == nullptr)
	{
		state = RenderStateFactory::Instance().Create(index);
		state->OnChanged += Bind(&RenderStateSet::OnStateChangedEvent, this);
		OnStateAdded(*state);
		mItems[index] = state;
	}
	return state;
}

Share<IRenderState> RenderStateSet::RemoveState(RenderStateType type)
{
	uint32 index = Math::CountTrailingZero((uint32)type);
	auto state = mItems[index];
	RETURN_NULL_IF_NULL(state);

	state->OnChanged -= Bind(&RenderStateSet::OnStateChangedEvent, this);
	OnStateRemoved(type);
	mItems[index] = nullptr;
	return state;
	
}

MEDUSA_END;
