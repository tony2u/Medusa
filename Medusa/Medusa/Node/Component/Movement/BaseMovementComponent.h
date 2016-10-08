// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Component/IComponent.h"
#include "Geometry/Point2.h"
#include "Geometry/GeometryDefines.h"
#include "Core/Pattern/Event.h"
#include "Node/Action/Basic/MoveByAction.h"
#include "Node/Action/Basic/MoveToAction.h"
#include "Node/Action/Basic/MoveBySpeedAction.h"

MEDUSA_BEGIN;

class BaseMovementComponent :public IComponent
{
	MEDUSA_DECLARE_COMPONENT(BaseMovementComponent, IComponent);
public:
	using MoveByAction = TMoveByAction<BaseMovementComponent>;
	using MoveToAction = TMoveToAction<BaseMovementComponent>;
	using MoveBySpeedAction = TMoveBySpeedAction<BaseMovementComponent>;
public:
	BaseMovementComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	float Velocity() const { return mVelocity; }
	void SetVelocity(float val) { mVelocity = val; }

	//move action interface
	Point3F Position()const;
	void SetPosition(const Point3F& val);
	void SetPosition(const Point2F& val);

protected:
	virtual void OnPositionChanged(const Point3F& oldPos, const Point3F& newPos){}
protected:
	float mVelocity=0.f;
};


MEDUSA_ENABLE_STATIC_CONSTRUCTOR(BaseMovementComponent);
MEDUSA_END;
