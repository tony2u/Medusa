// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
MEDUSA_BEGIN;

class Graph 
{
public:
	Graph();
	virtual ~Graph();

	void AddNode(GraphNode* node);
	GraphNode* NodeAt(uint index)const { return mNodes[index]; }
	void RemoveNode(GraphNode* node);

	void AddEdge(GraphEdge* edge);
	void RemoveEdge(GraphEdge* edge);

	GraphEdge* FindDirectedEdge(GraphNode* from, GraphNode* to)const;
	GraphEdge* FindEdge(GraphNode* from,GraphNode* to)const;

protected:
	List<GraphNode*> mNodes;
	List<GraphEdge*> mEdges;
};

MEDUSA_END;
