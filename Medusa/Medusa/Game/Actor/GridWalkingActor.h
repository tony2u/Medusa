// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Geometry/Grid/GridMap.h"

MEDUSA_BEGIN;

class GridWalkingActor :public INode
{
	MEDUSA_NODE(GridWalkingActor, INode);
public:
	GridWalkingActor(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);

	virtual ~GridWalkingActor(void);
	virtual bool Initialize() override;

	GridMap* Map() const { return mMap; }
	void SetMap(GridMap* val) { mMap = val; }
	uint AgentCapablity() const;
	void SetAgentCapablity(uint val);
protected:
	GridPathMovementComponent* mPathMovementComponent = nullptr;
	GridDistanceWanderMovementComponent* mWanderMovementComponent = nullptr;

	AnimatorComponent* mAnimator;

	GridMap* mMap=nullptr;
	
};

MEDUSA_END;
