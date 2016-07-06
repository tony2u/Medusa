// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseRenderStateTreeNode.h"
#include "Core/Pattern/AutoIncreaseId.h"
#include "RenderStateTreeCompositeNode.h"
#include "Graphics/State/RenderStateMachine.h"

MEDUSA_BEGIN;

BaseRenderStateTreeNode::BaseRenderStateTreeNode(const Share<IRenderState>& state /*= nullptr*/, RenderStateTreeCompositeNode* parent /*= nullptr*/)
	:mParent(parent)
{
	if (state != nullptr)
	{
		mState = state->Clone();
	}
	else
	{
		mState = nullptr;
	}

	mId = AutoIncreaseId<BaseRenderStateTreeNode>::New();
}

BaseRenderStateTreeNode::~BaseRenderStateTreeNode(void)
{
	AutoIncreaseId<BaseRenderStateTreeNode>::Deprecate(mId);
}

void BaseRenderStateTreeNode::Apply()
{
	if (mState!=nullptr)
	{
		RenderStateMachine::Instance().Push(mState);
	}
	if (mParent!=nullptr)
	{
		mParent->Apply();
	}
}

void BaseRenderStateTreeNode::Restore()
{
	if (mState!=nullptr)
	{
		RenderStateMachine::Instance().Pop(mState);
	}
	if (mParent != nullptr)
	{
		mParent->Restore();
	}
}


MEDUSA_END;