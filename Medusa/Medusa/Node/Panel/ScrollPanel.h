// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Panel/IPanel.h"
#include "Geometry/ScrollDirection.h"
MEDUSA_BEGIN;


enum class ScrollBarVisibility
{
	Disabled = -1,
	Auto=0,	//only visible on scrolling
	AlwaysVisible = 2,
	VisibleIfNeed = 3,
};

class ScrollPanel :public IPanel
{
	
	MEDUSA_DECLARE_RTTI;
public:
	ScrollPanel(StringRef name = StringRef::Empty, ScrollDirection direction = ScrollDirection::FreeFromCurrent);
	virtual ~ScrollPanel(void);
	virtual PanelType GetPanelType()const override{return PanelType::Scroll;}
public:
	virtual bool OnUpdate(float dt,NodeUpdateFlags flag = NodeUpdateFlags::None)override;

	virtual void ScrollTo(Point2F offset);
	virtual void ScrollBy(Point2F offset);
	virtual void ScrollToStart();
	virtual void ScrollToEnd();

public:
	bool IsVertical()const;
	bool IsHorizontal()const;

	ScrollDirection GetScrollDirection()const;
	virtual void SetScrollDirection(ScrollDirection direction);

	ScrollBarVisibility HorizontalScrollBarVisibility() const { return mHorizontalScrollBarVisibility; }
	void SetHorizontalScrollBarVisibility(ScrollBarVisibility val);

	ScrollBarVisibility VerticalScrollBarVisibility() const { return mVerticalScrollBarVisibility; }
	void SetVerticalScrollBarVisibility(ScrollBarVisibility val);

	float HorizontalScrollBarHeight() const { return mHorizontalScrollBarHeight; }
	void SetHorizontalScrollBarHeight(float val);

	float VerticalScrollBarWidth() const { return mVerticalScrollBarWidth; }
	void SetVerticalScrollBarWidth(float val);

	IScrollMathModel* ScrollModel() const { return mScrollModel; }
	void SetScrollModel(IScrollMathModel* val);
protected:
	virtual bool ArrangeChildren(const Rect2F& limitRect=Rect2F::Zero,NodeLayoutArrangeFlags arrangeFlags=NodeLayoutArrangeFlags::None)override;

	virtual void OnSwipeBegin(INode* sender,SwipeBeginGestureEventArg& e);
	virtual void OnSwipeMoved(INode* sender,SwipeMovedGestureEventArg& e);
	virtual void OnSwipeFailed(INode* sender,SwipeFailedGestureEventArg& e);
	virtual void OnSwipeSuccess(INode* sender,SwipeSuccessGestureEventArg& e);

	virtual void OnMoveChildren();
	virtual void OnInitializeTargetBoundingBox();

	virtual bool IsSensitiveToChildLayoutChanged(const ILayoutable& sender,NodeLayoutChangedFlags changedFlag) override;

protected:
	virtual void UpdateScrollStatus();

	virtual void OnUpdateScrollBar();
	virtual void OnBeginMove();
	virtual void OnEndMove();
protected:
	SwipeGestureRecognizer* mSwipeGestureRecognizer=nullptr;

	//scroll bar
	ScrollBarVisibility mHorizontalScrollBarVisibility= ScrollBarVisibility::VisibleIfNeed;
	ScrollBarVisibility mVerticalScrollBarVisibility= ScrollBarVisibility::Auto;
	Color4F mScrollBarColor;
	float mHorizontalScrollBarHeight=3.f;
	float mVerticalScrollBarWidth=3.f;
	float mScrollBarOpacityFadeSpeed=1.f;	//the opacity(0~1.f) changed per second


	IScrollMathModel* mScrollModel=nullptr;
	INode* mHorizontalScrollBar=nullptr;
	INode* mVerticalScrollBar=nullptr;
};



MEDUSA_END;
