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
	typedef List<BaseRenderStateTreeNode*> RenderStateTreeNodeList;

	RenderStateTreeCompositeNode(IRenderState* state = nullptr, RenderStateTreeCompositeNode* parent = nullptr);
	virtual ~RenderStateTreeCompositeNode(void);
	virtual RenderStateTreeLeafNode* FindUniqueNode(const RenderStateSet& stateSet, RenderStateType type)override;
	bool IsEmpty()const;
	bool IsSingle()const;

	void Remove(BaseRenderStateTreeNode* node);

	void Delete(BaseRenderStateTreeNode* node);


private:
	BaseRenderStateTreeNode* FindNodeByState(IRenderState* state)const;

protected:
	RenderStateTreeNodeList mNextStateNodes;
	BaseRenderStateTreeNode* mNextNullStateNode;
};

MEDUSA_END;
