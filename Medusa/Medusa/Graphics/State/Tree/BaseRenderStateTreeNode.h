// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/Dictionary.h"
#include "Graphics/State/RenderStateType.h"
#include "Graphics/State/IRenderState.h"

MEDUSA_BEGIN;


class BaseRenderStateTreeNode 
{
public:
	//typedef Dictionary<IRenderState*, RenderStateTreeNode*, DefaultPointerHashCoder<IRenderState*>, NoHashCoder<RenderStateTreeNode*>, PointerEqualCompare<IRenderState*>, NoCompare<RenderStateTreeNode*>> RenderStateTreeNodeDict;
	BaseRenderStateTreeNode(IRenderState* state = nullptr, RenderStateTreeCompositeNode* parent = nullptr);
	virtual ~BaseRenderStateTreeNode(void);

	virtual RenderStateTreeLeafNode* FindUniqueNode(const RenderStateSet& stateSet, RenderStateType type) { return nullptr; }
	uint Id() const { return mId; }
	IRenderState* State() const { return mState; }
	RenderStateTreeCompositeNode* Parent() const { return mParent; }

	void Apply();
	void Restore();

protected:
	RenderStateTreeCompositeNode* mParent;
	uint mId;
	IRenderState* mState;	//null able
	
};

MEDUSA_END;
