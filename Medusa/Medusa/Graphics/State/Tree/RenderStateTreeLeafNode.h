// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseRenderStateTreeNode.h"

MEDUSA_BEGIN;


class RenderStateTreeLeafNode :public BaseRenderStateTreeNode, public ISharableSingleThread
{
public:
	RenderStateTreeLeafNode(IRenderState* state, RenderStateTreeCompositeNode* parent);
	~RenderStateTreeLeafNode(void);
	
	
};

MEDUSA_END;
