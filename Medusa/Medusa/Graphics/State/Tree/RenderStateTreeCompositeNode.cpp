// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderStateTreeCompositeNode.h"
#include "Graphics/State/IRenderState.h"
#include "Graphics/State/RenderStateSet.h"
#include "RenderStateTreeLeafNode.h"

MEDUSA_BEGIN;

RenderStateTreeCompositeNode::RenderStateTreeCompositeNode(const Share<IRenderState>& state /*= nullptr*/, RenderStateTreeCompositeNode* parent /*= nullptr*/)
	:BaseRenderStateTreeNode(state, parent)
{
	mNextNullStateNode = nullptr;
}

RenderStateTreeCompositeNode::~RenderStateTreeCompositeNode(void)
{
	mNextNullStateNode = nullptr;
	mNextStateNodes.Clear();
}

Share<RenderStateTreeLeafNode> RenderStateTreeCompositeNode::FindUniqueNode(const RenderStateSet& stateSet, RenderStateType type)
{
	RenderStateType lastType = (RenderStateType)(1<<((uint32)RenderStateType::Count - 1));
	RenderStateType nextType = (RenderStateType)((uint32)type <<1);
	bool isMiddle = type < lastType;

	auto state = stateSet.GetState(type);

	if (isMiddle)
	{
		if (state == nullptr)
		{
			if (mNextNullStateNode == nullptr)
			{
				mNextNullStateNode = new RenderStateTreeCompositeNode(nullptr, this);
			}

			auto nextNode = mNextNullStateNode.CastPtr<RenderStateTreeCompositeNode>();
			return nextNode->FindUniqueNode(stateSet, nextType);
		}
		else
		{
			auto nextNode = FindNodeByState(state).CastPtr<RenderStateTreeCompositeNode>();
			if (nextNode == nullptr)
			{
				nextNode = new RenderStateTreeCompositeNode(state, this);
				mNextStateNodes.Add(nextNode);
			}
			return nextNode->FindUniqueNode(stateSet, nextType);
		}
	}
	else
	{
		if (state == nullptr)
		{
			if (mNextNullStateNode == nullptr)
			{
				mNextNullStateNode = new RenderStateTreeLeafNode(nullptr, this);
			}
			return mNextNullStateNode.CastPtr<RenderStateTreeLeafNode>();
		}
		else
		{
			auto nextNode = FindNodeByState(state).CastPtr<RenderStateTreeLeafNode>();
			if (nextNode == nullptr)
			{
				nextNode = new RenderStateTreeLeafNode(state, this);
				mNextStateNodes.Add(nextNode);
			}

			return nextNode;
		}
	}
}

Share<BaseRenderStateTreeNode> RenderStateTreeCompositeNode::FindNodeByState(const Share<IRenderState>& state) const
{
	for(auto curStateNode: mNextStateNodes)
	{
		auto curState = curStateNode->State();
		if (curState == state || (curState != nullptr&&curState->Equals(*state)))
		{
			return curStateNode;
		}
	}
	return nullptr;
}

void RenderStateTreeCompositeNode::Remove(const Share<BaseRenderStateTreeNode>& node)
{
	if (mNextNullStateNode == node)
	{
		mNextNullStateNode = nullptr;
	}
	else
	{
		mNextStateNodes.Remove(node);
	}
}

bool RenderStateTreeCompositeNode::IsEmpty() const
{
	return mNextNullStateNode == nullptr&&mNextStateNodes.IsEmpty();
}

bool RenderStateTreeCompositeNode::IsSingle() const
{
	if (mNextNullStateNode==nullptr)
	{
		return mNextStateNodes.Count() == 1;
	}
	else
	{
		return mNextStateNodes.IsEmpty();
	}
}

MEDUSA_END;