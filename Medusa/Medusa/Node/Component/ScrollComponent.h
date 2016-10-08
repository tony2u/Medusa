// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Component/IComponent.h"
#include "Geometry/Scroll/IScrollMathModel.h"

MEDUSA_BEGIN;

class ScrollComponent :public IComponent
{
	MEDUSA_DECLARE_COMPONENT(ScrollComponent,IComponent);
public:
	ScrollComponent(const StringRef& name = StringRef::Empty, int priority = 0, void* userData = nullptr);
	virtual ~ScrollComponent(void);

	virtual bool Update(float dt)override;

	bool Initialize(const Rect2F& container, const Rect2F& window, ScrollDirection direction = ScrollDirection::HorizontalFromLeft,bool isReverse=false);
	bool IsReverse() const { return mIsReverse; }
	void EnableReverse(bool val) { mIsReverse = val; }

	IScrollMathModel* ScrollModel() const { return mScrollModel; }
	void SetScrollModel(IScrollMathModel* val);
protected:
	virtual void OnScroll();
protected:
	bool mIsReverse;	//used to control window to move in opposite direction
	IScrollMathModel* mScrollModel = nullptr;
	
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(ScrollComponent);

//[PRE_DECLARE_BEGIN]
typedef TScrollToAction<ScrollComponent> ScrollComponentScrollToAction;
typedef TScrollByAction<ScrollComponent> ScrollComponentScrollByAction;
typedef TScrollBySpeedAction<ScrollComponent> ScrollComponentScrollBySpeedAction;
typedef TScrollByPageAction<ScrollComponent> ScrollComponentScrollByPageAction;
typedef TScrollToPageAction<ScrollComponent> ScrollComponentScrollToPageAction;

//[PRE_DECLARE_END]

MEDUSA_END;
