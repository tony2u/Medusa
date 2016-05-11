// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;

class GraphEdge
{
public:
	GraphEdge(GraphNode* from, GraphNode* to, float weight = 1.f);
	virtual ~GraphEdge();

	GraphNode* From() const { return mFrom; }
	void SetFrom(GraphNode* val) { mFrom = val; }

	GraphNode* To() const { return mTo; }
	void SetTo(GraphNode* val) { mTo = val; }

	uint Index() const { return mIndex; }
	void SetIndex(uint val) { mIndex = val; }

	float Weight() const { return mWeight; }
	void SetWeight(float val) { mWeight = val; }
protected:
	uint mIndex;
	GraphNode* mFrom;
	GraphNode* mTo;
	float mWeight;
};

MEDUSA_END;
