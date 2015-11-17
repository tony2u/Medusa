// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "GraphEdge.h"

MEDUSA_BEGIN;

GraphEdge::GraphEdge(GraphNode* from, GraphNode* to, float weight/*=1.f*/)
	:mIndex(0),
	mFrom(from),
	mTo(to), 
	mWeight(weight)
{
	
}

GraphEdge::~GraphEdge()
{

}

MEDUSA_END;