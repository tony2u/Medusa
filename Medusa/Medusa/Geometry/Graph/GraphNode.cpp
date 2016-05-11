// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;
GraphNode::GraphNode()
	:mIndex(0)
{

}

void GraphNode::AddEdge(GraphEdge* edge)
{
	mEdges.Add(edge);
	if (edge->From()==this)
	{
		mOutEdges.Add(edge);
	}
	else if (edge->To()==this)
	{
		mInEdges.Add(edge);
	}
	else
	{
		Log::AssertFailedFormat("Added an adge that doesn't belong to this node: {}", mIndex);
	}
}

void GraphNode::RemoveEdge(GraphEdge* edge)
{
	if (edge->To()==this)
	{
		mInEdges.RemoveUnordered(edge);
	}
	else
	{
		mOutEdges.RemoveUnordered(edge);
	}
	mEdges.RemoveUnordered(edge);
}


void GraphNode::ClearEdges()
{
	mEdges.Clear();
	mInEdges.Clear();
	mOutEdges.Clear();
}

MEDUSA_END;
