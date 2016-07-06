// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ChangedNodeCollector.h"
#include "Node/INode.h"

MEDUSA_BEGIN;

ChangedNodeCollector::ChangedNodeCollector()
{
	
}

ChangedNodeCollector::~ChangedNodeCollector(void)
{
	
}

bool ChangedNodeCollector::Visit(INode* node)
{
	if (node->RenderableChangedFlag()!=RenderableChangedFlags::None)
	{
		mNodes.Add(node);
	}
	return true;
}

void ChangedNodeCollector::Clear()
{
	FOR_EACH_TO_CLEAR(mNodes, ClearChangedFlag());
}

MEDUSA_END;