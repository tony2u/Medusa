// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IScrollMathModel.h"

MEDUSA_BEGIN;

class SpringScrollMathModel:public IScrollMathModel
{
public:
	SpringScrollMathModel(ScrollDirection direction = ScrollDirection::FreeFromCurrent);
	virtual ~SpringScrollMathModel(void);

public:
	virtual bool UpdateModel(float dt);
	virtual void ScrollTo(Point2F offset);
	virtual void ScrollBy(Point2F movement);
	virtual void Release();
	virtual void StartScrolling(Point2F initialVelocity);

protected:
	bool NeedSpringOnScrolling()const;
	bool NeedSpringOnSpring()const;
	virtual void OnUpdate();
	virtual void OnScrollingEnd();
	virtual void OnRestrictScroll();

	Point2F CalculateSpringAccelerate()const;
	Point2F CalculateScrollAccelerate()const;

protected:
	RangeF mSpringLimitX;	//cache
	RangeF mSpringLimitY;	//cache

	//spring effect
	Point2F mSpringSizePercent;	//

	float mSpringFactor;

	float mDampingStartFactor;
	float mDampingFactor;

	float mInitialVelocityFactor;

};

MEDUSA_END;
