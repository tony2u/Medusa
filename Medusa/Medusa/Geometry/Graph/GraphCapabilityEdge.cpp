// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GraphCapabilityEdge.h"

MEDUSA_BEGIN;

GraphCapabilityEdge::GraphCapabilityEdge(GraphNode* from, GraphNode* to, float weight/*=0.f*/)
	:GraphEdge(from,to,weight),
	mCapability(0)
{

}


MEDUSA_END;