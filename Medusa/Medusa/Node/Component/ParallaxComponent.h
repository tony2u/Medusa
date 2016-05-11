// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Component/IComponent.h"
#include "Core/Pattern/TuplePattern.h"
#include "Geometry/Point3.h"
#include "Core/Collection/Dictionary.h"
MEDUSA_BEGIN;


class ParallaxComponent :public IComponent
{
	MEDUSA_DECLARE_COMPONENT;
	MEDUSA_TUPLE_2(ParallaxInfo, Point3F, Ratio, Point3F, Offset);
public:
	ParallaxComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);

	virtual ~ParallaxComponent(void);

	const Point3F& Position() const { return mPosition; }
	void SetPosition(const Point3F& val);

	void EnableParallax(INode* node, const Point3F& ratio = Point3F::One, const Point3F& offset = Point3F::Zero);
	void DisableParallax(INode* node);

	void DisableAllParallax();


	bool IsReverse() const { return mIsReverse; }
	void EnableReverse(bool val) { mIsReverse = val; }
protected:
	Point3F mPosition;
	Dictionary<INode*, ParallaxInfo> mItems;
	bool mIsReverse;
	
};


//[PRE_DECLARE_BEGIN]
typedef TMoveToAction<ParallaxComponent> ParallaxComponentMoveToAction;
typedef TMoveByAction<ParallaxComponent> ParallaxComponentMoveByAction;
typedef TMoveBySpeedAction<INode> ParallaxComponentMoveBySpeedAction;
//[PRE_DECLARE_END]

MEDUSA_END;
