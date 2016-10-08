// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Component/Movement/BaseMovementComponent.h"
#include "Geometry/GeometryDefines.h"
#include "Core/Pattern/Component/ComponentFactory.h"

MEDUSA_BEGIN;

class BaseGridMovementComponent :public BaseMovementComponent
{
	MEDUSA_DECLARE_COMPONENT(BaseGridMovementComponent, BaseMovementComponent);
public:
	using BaseMovementComponent::BaseMovementComponent;

	GridMap* Map() const { return mMap; }
	void SetMap(GridMap* val) { mMap = val; }

	uint AgentCapablity() const { return mAgentCapablity; }
	void SetAgentCapablity(uint val) { mAgentCapablity = val; }
	
	Point2I CurrentIndex()const;

	MoveDirection Direction()const { return mDirection; }
	Event<void(MoveDirection)> OnDirectionChanged;
protected:
	void UpdateDirection(Point2F from, Point2F to);
	virtual void OnPositionChanged(const Point3F& oldPos, const Point3F& newPos);
protected:
	GridMap* mMap = nullptr;
	MoveDirection mDirection = MoveDirection::None;
	uint mAgentCapablity = Math::UIntMaxValue;	//default can walk anywhere

};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(BaseGridMovementComponent);
MEDUSA_END;
