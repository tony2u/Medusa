// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderStateTree.h"
#include "Graphics/State/Tree/BaseRenderStateTreeNode.h"
#include "Core/Pattern/AutoIncreaseId.h"
#include "RenderStateTreeCompositeNode.h"
#include "RenderStateTreeLeafNode.h"


MEDUSA_BEGIN;

RenderStateTree::RenderStateTree()
{
	mRoot = nullptr;
}

RenderStateTree::~RenderStateTree()
{

}

bool RenderStateTree::Initialize()
{
	if (mRoot == nullptr)
	{
		mRoot = new RenderStateTreeCompositeNode();
	}
	if (mEmptyNode == nullptr)
	{
		mEmptyNode = new RenderStateTreeLeafNode(nullptr, nullptr);
		mEmptyNode->Retain();
	}
	return true;
}

bool RenderStateTree::Uninitialize()
{
	SAFE_DELETE(mRoot);
	SAFE_DELETE(mEmptyNode);

	return true;
}


RenderStateTreeLeafNode* RenderStateTree::FindUniqueNode(const RenderStateSet& state)
{
	RenderStateType type = (RenderStateType)0;	//first
	return mRoot->FindUniqueNode(state, type);
}

uint RenderStateTree::MinId() const
{
	return AutoIncreaseId<BaseRenderStateTreeNode>::Min();
}

uint RenderStateTree::CalcuateId(const RenderStateTreeLeafNode& node) const
{
	return node.Id() - MinId();
}

void RenderStateTree::Release(RenderStateTreeLeafNode* node)
{
	RETURN_IF_NULL(node);
	node->Release();

	if (node->IsShared())
	{
		return;
	}

	auto* parent = node->Parent();
	RETURN_IF_NULL(parent);
	parent->Remove(node);

	//find most top empty parent
	if (parent->IsEmpty())
	{
		auto* top = parent;
		auto* prevTop = parent;
		do
		{
			prevTop = top;
			top = top->Parent();
		}while (top != mRoot&&top->IsSingle());

		top->Delete(prevTop);
	}


}



MEDUSA_END;
