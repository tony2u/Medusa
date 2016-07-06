// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graph.h"
#include "GraphNode.h"
#include "GraphEdge.h"

MEDUSA_BEGIN;

Graph::Graph()
{

}

Graph::~Graph()
{
	SAFE_DELETE_COLLECTION(mNodes);
	SAFE_DELETE_COLLECTION(mEdges);
}

void Graph::AddNode(GraphNode* node)
{
	mNodes.Add(node);
	node->SetIndex((uint)mNodes.Count() - 1);
}


void Graph::AddEdge(GraphEdge* edge)
{
	mEdges.Add(edge);
	edge->SetIndex((uint)mEdges.Count() - 1);
}

GraphEdge* Graph::FindDirectedEdge(GraphNode* from, GraphNode* to) const
{
	for (GraphEdge* edge : from->OutEdges())
	{
		if (edge->To() == to)
		{
			return edge;
		}
	}
	return nullptr;
}

GraphEdge* Graph::FindEdge(GraphNode* from, GraphNode* to) const
{
	for (GraphEdge* edge : from->Edges())
	{
		if ((edge->From()==from&&edge->To()==to)||(edge->From()==to&&edge->To()==from))
		{
			return edge;
		}
	}
	return nullptr;
}



void Graph::RemoveEdge(GraphEdge *edge)
{
	edge->From()->RemoveEdge(edge);
	edge->To()->RemoveEdge(edge);
	mEdges.RemoveSwap(edge);
}

void Graph::RemoveNode(GraphNode* node)
{
	size_t count=node->Edges().Count();
	FOR_EACH_SIZE(i, count)
	{
		GraphEdge* edge=node->Edges().Last();
		RemoveEdge(edge);
		delete edge;
	}
	node->ClearEdges();
}



MEDUSA_END;