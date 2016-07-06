// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/IRenderState.h"
#include "RenderStateFactory.h"


MEDUSA_BEGIN;

IRenderState::IRenderState()
{
}

IRenderState::~IRenderState()
{

}

Share<IRenderState> IRenderState::Clone() const
{
	uint32 index = Math::CountTrailingZero((uint32)Type());
	auto state= RenderStateFactory::Instance().Create(index);
	state->CopyFrom(*this);
	return state;
}

bool IRenderState::Equals(const IRenderState& state) const
{
	RETURN_FALSE_IF_FALSE(IsExactly(state.Class()));
	RETURN_FALSE_IF_NOT_EQUAL(HashCode(),state.HashCode());
	return true;
}


void IRenderState::UpdateWorldState(const Share<IRenderState>& selfRenderState, const Share<IRenderState>& parentRenderState, const Matrix4& selfWorldMatrix)
{
	if (selfRenderState != nullptr)
	{
		//use self first
		MEDUSA_ASSERT(selfRenderState->Type() == Type(), "Cannot copy render state with different type");
		CopyFrom(*selfRenderState);
	}
	else if (parentRenderState!=nullptr)
	{
		MEDUSA_ASSERT(parentRenderState->Type() == Type(), "Cannot copy render state with different type");
		CopyFrom(*parentRenderState);
	}
}

void IRenderState::OnStateChanged()
{
	OnChanged(*this);
}


MEDUSA_END;