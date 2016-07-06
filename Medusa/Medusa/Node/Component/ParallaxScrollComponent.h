// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "ScrollComponent.h"
#include "Geometry/Point3.h"

MEDUSA_BEGIN;

class ParallaxScrollComponent :public ScrollComponent
{
	MEDUSA_DECLARE_COMPONENT(ParallaxScrollComponent,ScrollComponent);
public:
	ParallaxScrollComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	virtual ~ParallaxScrollComponent(void);

	void EnableParallax(INode* node, const Point3F& ratio = Point3F::One, const Point3F& offset = Point3F::Zero);
	void DisableParallax(INode* node);

	void DisableAllParallax();
protected:
	virtual void OnScroll() override;
protected:
	ParallaxComponent* mParallaxComponent;
};




MEDUSA_END;
