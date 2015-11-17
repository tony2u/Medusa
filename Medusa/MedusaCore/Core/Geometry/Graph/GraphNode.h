// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
MEDUSA_BEGIN;

class GraphNode
{
public:
	GraphNode();
	virtual ~GraphNode() {}
	uint Index() const { return mIndex; }
	void SetIndex(uint val) { mIndex = val; }

	void AddEdge(GraphEdge* edge);
	void RemoveEdge(GraphEdge* edge);

	GraphEdge* EdgeAt(uint index)const { return mEdges[index]; }
	const List<GraphEdge*>& Edges() const { return mEdges; }
	const List<GraphEdge*>& OutEdges() const { return mOutEdges; }
	const List<GraphEdge*>& InEdges() const { return mInEdges; }

	void ClearEdges();
protected:
	uint mIndex;
	List<GraphEdge*> mOutEdges;
	List<GraphEdge*> mInEdges;
	List<GraphEdge*> mEdges;
};


MEDUSA_END;
