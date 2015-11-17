// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderStateTreeLeafNode.h"
#include "RenderStateTreeCompositeNode.h"

MEDUSA_BEGIN;
RenderStateTreeLeafNode::RenderStateTreeLeafNode(IRenderState* state, RenderStateTreeCompositeNode* parent)
	:BaseRenderStateTreeNode(state, parent)
{

}

RenderStateTreeLeafNode::~RenderStateTreeLeafNode(void)
{
	
}


MEDUSA_END;