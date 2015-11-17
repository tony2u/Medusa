// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderStateTreeCompositeNode.h"
#include "Graphics/State/IRenderState.h"
#include "Graphics/State/RenderStateSet.h"
#include "RenderStateTreeLeafNode.h"

MEDUSA_BEGIN;

RenderStateTreeCompositeNode::RenderStateTreeCompositeNode(IRenderState* state /*= nullptr*/, RenderStateTreeCompositeNode* parent /*= nullptr*/)
	:BaseRenderStateTreeNode(state, parent)
{
	mNextNullStateNode = nullptr;
}

RenderStateTreeCompositeNode::~RenderStateTreeCompositeNode(void)
{
	SAFE_DELETE(mNextNullStateNode);
	SAFE_DELETE_COLLECTION(mNextStateNodes);
}

RenderStateTreeLeafNode* RenderStateTreeCompositeNode::FindUniqueNode(const RenderStateSet& stateSet, RenderStateType type)
{
	RenderStateType lastType = (RenderStateType)((uint32)RenderStateType::Count - 1);
	RenderStateType nextType = (RenderStateType)((uint32)type + 1);
	bool isMiddle = type < lastType;

	IRenderState* state = stateSet.GetState(type);

	if (isMiddle)
	{
		if (state == nullptr)
		{
			if (mNextNullStateNode == nullptr)
			{
				mNextNullStateNode = new RenderStateTreeCompositeNode(nullptr, this);
			}
			return mNextNullStateNode->FindUniqueNode(stateSet, nextType);
		}
		else
		{
			RenderStateTreeCompositeNode* nextNode = (RenderStateTreeCompositeNode*)FindNodeByState(state);
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
				((RenderStateTreeLeafNode*)mNextNullStateNode)->Retain();
			}
			return (RenderStateTreeLeafNode*)mNextNullStateNode;
		}
		else
		{
			RenderStateTreeLeafNode* nextNode = (RenderStateTreeLeafNode*)FindNodeByState(state);
			if (nextNode == nullptr)
			{
				nextNode = new RenderStateTreeLeafNode(state, this);
				mNextStateNodes.Add(nextNode);
				nextNode->Retain();
			}

			return nextNode;
		}
	}
}

BaseRenderStateTreeNode* RenderStateTreeCompositeNode::FindNodeByState(IRenderState* state) const
{
	FOR_EACH_COLLECTION(i, mNextStateNodes)
	{
		BaseRenderStateTreeNode* curStateNode = *i;
		IRenderState* curState = curStateNode->State();
		if (curState == state || (curState != nullptr&&curState->Equals(*state)))
		{
			return curStateNode;
		}
	}
	return nullptr;
}

void RenderStateTreeCompositeNode::Remove(BaseRenderStateTreeNode* node)
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

void RenderStateTreeCompositeNode::Delete(BaseRenderStateTreeNode* node)
{
	Remove(node);
	SAFE_DELETE(node);
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