// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderStateSet.h"
#include "Core/Pattern/Ptr/LazyStrongPtr.inl"

#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/IRenderState.h"
#include "Graphics/State/BlendRenderState.h"
#include "Graphics/State/ScissorRenderState.h"
#include "Graphics/State/RenderStateMachine.h"


MEDUSA_BEGIN;


RenderStateSet::RenderStateSet()
{
}


RenderStateSet::~RenderStateSet(void)
{
}

RenderStateSet& RenderStateSet::operator=(const RenderStateSet& val)
{
	mBlendState = val.mBlendState;
	mScissorState = val.mScissorState;
	return *this;
}




bool RenderStateSet::Equals(const RenderStateSet& states) const
{
	return false;

}

void RenderStateSet::Apply()const
{
	if (mBlendState != nullptr)
	{
		RenderStateMachine::Instance().Push(mBlendState);
	}
	if (mScissorState != nullptr)
	{
		RenderStateMachine::Instance().Push(mScissorState);
	}

}


void RenderStateSet::Restore()const
{
	if (mBlendState != nullptr)
	{
		RenderStateMachine::Instance().Pop(mBlendState);
	}

	if (mScissorState != nullptr)
	{
		RenderStateMachine::Instance().Pop(mScissorState);
	}

}


bool RenderStateSet::EnableBlend(bool val)
{
	bool isChanged = false;
	if (mBlendState == nullptr)
	{
		mBlendState.Alloc();
		mBlendState->Retain();
		mBlendState->OnChanged += Bind(&RenderStateSet::OnStateChangedEvent, this);
		isChanged = true;
	}

	if (mBlendState->Enable(val))
	{
		return true;
	}
	return isChanged;
}

bool RenderStateSet::SetBlendFunc(GraphicsBlendSrcFunc srcFunc, GraphicsBlendDestFunc destFunc)
{
	bool isChanged = false;
	if (mBlendState == nullptr)
	{
		mBlendState.Alloc();
		mBlendState->Retain();
		mBlendState->OnChanged += Bind(&RenderStateSet::OnStateChangedEvent, this);
		isChanged = true;
	}

	if (mBlendState->SetBlendFunc(srcFunc, destFunc))
	{
		return true;
	}
	return isChanged;
}

bool RenderStateSet::IsBlendEnabled() const
{
	return mBlendState != nullptr&&mBlendState->IsEnabled();
}

bool RenderStateSet::RemoveBlend()
{
	if (mBlendState!=nullptr)
	{
		mBlendState.Release();
		OnStateRemoved(RenderStateType::Blend);
		return true;
	}
	return false;
}


BlendRenderState* RenderStateSet::BlendState()
{
	if (mBlendState == nullptr)
	{
		mBlendState.Alloc();
		mBlendState->Retain();
		mBlendState->OnChanged += Bind(&RenderStateSet::OnStateChangedEvent, this);
	}
	return mBlendState;
}

bool RenderStateSet::HasScissorBox() const
{
	return mScissorState != nullptr;
}


bool RenderStateSet::IsScissorEnabled() const
{
	return mScissorState != nullptr&&mScissorState->IsEnabled();
}

bool RenderStateSet::SetScissorBox(const Rect2F& val)
{
	bool isChanged = false;

	if (mScissorState == nullptr)
	{
		mScissorState.Alloc();
		mScissorState->Retain();
		mScissorState->OnChanged += Bind(&RenderStateSet::OnStateChangedEvent, this);
		isChanged = true;
	}

	if (mScissorState->SetScissorBox(val))
	{
		return true;

	}
	return isChanged;
}

bool RenderStateSet::EnableScissor(bool val)
{
	bool isChanged = false;

	if (mScissorState == nullptr)
	{
		mScissorState.Alloc();
		mScissorState->Retain();
		mScissorState->OnChanged += Bind(&RenderStateSet::OnStateChangedEvent, this);
		isChanged = true;
	}

	if (mScissorState->Enable(val))
	{
		return true;

	}
	return isChanged;
}

bool RenderStateSet::RemoveScissor()
{
	if (mScissorState!=nullptr)
	{
		mScissorState.Release();
		OnStateRemoved(RenderStateType::Scissor);
		return true;
	}
	return false;
}

const Rect2F* RenderStateSet::TryGetScissorBox() const
{
	RETURN_NULL_IF_NULL(mScissorState);
	return &mScissorState->ScissorBox();
}

const Rect2F& RenderStateSet::GetScissorBoxOrEmpty() const
{
	if (mScissorState != nullptr)
	{
		return mScissorState->ScissorBox();
	}
	return Rect2F::Zero;
}


void RenderStateSet::UpdateFromParent(const RenderStateSet& selfRenderState, const RenderStateSet& parentRenderState, const Matrix& selfWorldMatrix, RenderStateType flag)
{
	
	if (MEDUSA_HAS_FLAG(flag,RenderStateType::Blend))
	{
		//do not inherit
		mBlendState = selfRenderState.mBlendState;
	}

	if (MEDUSA_HAS_FLAG(flag, RenderStateType::Scissor))
	{
		if (selfRenderState.mScissorState == nullptr)
		{
			mScissorState = parentRenderState.mScissorState;
		}
		else
		{
			if (parentRenderState.mScissorState == nullptr)
			{
				mScissorState = selfRenderState.mScissorState;
				mScissorState->Tansform(selfWorldMatrix);

			}
			else
			{
				mScissorState = selfRenderState.mScissorState;
				mScissorState->Tansform(selfWorldMatrix);

				if (parentRenderState.mScissorState->IsEnabled())
				{
					Rect2F result = Rect2F::Intersect(mScissorState->ScissorBox(), parentRenderState.mScissorState->ScissorBox());
					mScissorState->SetScissorBox(result);
					mScissorState->Enable(true);
				}
			}
		}
	}
}

void RenderStateSet::UpdateFromSelf(const RenderStateSet& selfRenderState, const Matrix& selfWorldMatrix, RenderStateType flag)
{
	if (MEDUSA_HAS_FLAG(flag, RenderStateType::Blend))
	{
		mBlendState = selfRenderState.mBlendState;
	}

	if (MEDUSA_HAS_FLAG(flag, RenderStateType::Scissor))
	{
		mScissorState = selfRenderState.mScissorState;
		if (mScissorState!=nullptr)
		{
			mScissorState->Tansform(selfWorldMatrix);
		}
	}
}

void RenderStateSet::OnStateChangedEvent(IRenderState& state)
{
	OnStateChanged(state);
}

IRenderState* RenderStateSet::GetState(RenderStateType type) const
{
	IRenderState* outState;
	TryGetState(type,outState);
	return outState;
}

bool RenderStateSet::TryGetState(RenderStateType type, IRenderState*& outState) const
{
	switch (type)
	{
		case RenderStateType::Blend:
			outState = mBlendState;
			return true;
		case RenderStateType::Scissor:
			outState = mScissorState;
			return true;
		default:
			outState = nullptr;
			return false;
	}
}


MEDUSA_END;
