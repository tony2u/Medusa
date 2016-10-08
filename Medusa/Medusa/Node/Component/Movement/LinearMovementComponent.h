// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseMovementComponent.h"

MEDUSA_BEGIN;

class LinearMovementComponent :public BaseMovementComponent
{
	MEDUSA_DECLARE_COMPONENT(LinearMovementComponent, BaseMovementComponent);
public:
	LinearMovementComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);

	virtual void MoveBy(Point2F delta);
	virtual void MoveTo(Point2F to);

	virtual bool Update(float dt)override;
	virtual MoveDirection Direction()const;
protected:
	virtual void OnMovementChanged(Point2F delta);
	void UpdateK();
protected:
	float mAcceleration = 0.f;
	float mDeceleration = 0.f;

	Point2F mMovementLeft;
	Point2F mMovementK;
};
MEDUSA_ENABLE_STATIC_CONSTRUCTOR(LinearMovementComponent);


MEDUSA_END;
