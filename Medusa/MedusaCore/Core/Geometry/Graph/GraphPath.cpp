// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "GraphPath.h"

MEDUSA_BEGIN;

void GraphPath::AddNode(GraphNode* node)
{
	mNodes.Add(node);
}

MEDUSA_END;