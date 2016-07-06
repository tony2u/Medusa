// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseRenderStateTreeNode.h"

MEDUSA_BEGIN;


class RenderStateTreeCompositeNode :public BaseRenderStateTreeNode
{
	friend class RenderStateTreeLeafNode;
public:
	typedef List<Share<BaseRenderStateTreeNode>> RenderStateTreeNodeList;

	RenderStateTreeCompositeNode(const Share<IRenderState>& state = nullptr, RenderStateTreeCompositeNode* parent = nullptr);
	virtual ~RenderStateTreeCompositeNode(void);
	Share<RenderStateTreeLeafNode> FindUniqueNode(const RenderStateSet& stateSet, RenderStateType type);
	bool IsEmpty()const;
	bool IsSingle()const;

	void Remove(const Share<BaseRenderStateTreeNode>& node);
private:
	Share<BaseRenderStateTreeNode> FindNodeByState(const Share<IRenderState>& state)const;

protected:
	RenderStateTreeNodeList mNextStateNodes;
	Share<BaseRenderStateTreeNode> mNextNullStateNode;
};

MEDUSA_END;
