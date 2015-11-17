// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "GraphEdge.h"
MEDUSA_BEGIN;

class GraphCapabilityEdge :public GraphEdge
{
public:
	GraphCapabilityEdge(GraphNode* from, GraphNode* to, float weight = 0.f);
	int Capability() { return mCapability; }
	void SetCapability(uint val) { mCapability = val; }
	bool IsPassable(uint agentCapability)const { return (mCapability&agentCapability) == mCapability; }
protected:
	uint mCapability;
};

MEDUSA_END;
