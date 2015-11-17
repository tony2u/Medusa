// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Range.h"
#include "Core/Geometry/ScrollDirection.h"

MEDUSA_BEGIN;

//Note: window maybe smaller than container and container maybe smaller than window too
class IScrollMathModel
{
public:
	enum class ScrollState
	{
		None,
		Begin,
		StaticScroll,
		Scrolling,
		Spring,
		End
	};
public:
	IScrollMathModel(ScrollDirection direction = ScrollDirection::FreeFromCurrent);
	virtual ~IScrollMathModel(void);
public:
	void Initialize(const Size2F& containerSize, const Rect2F& window);
	void Initialize(const Size2F& containerSize, const Size2F& windowSize);
	void Initialize(const Rect2F& container, const Rect2F& window);

	ScrollDirection Direction() const { return mDirection; }
	void SetDirection(ScrollDirection val);

	bool IsVertical()const;
	bool IsHorizontal()const;

	ScrollState State() const { return mState; }
	const Rect2F& CurrentWindow() const { return mCurrentWindow; }

	Point2F Movement()const { return mCurrentWindow.Origin - mPrevWindow.Origin; }
	void ApplyMovement() { mPrevWindow = mCurrentWindow; }
	Point2F MovementToEnd()const;	//on direction
	Point2F MovementToStart()const;	//on direction


	bool IsRectVisible(const Rect2F& rect)const;
	Point2F ConvertToWindowSpace(Point2F pos);

	Point2F Offset()const;
	float OffsetX()const;
	float OffsetY()const;



	virtual void StaticScroll(Point2F movement);
	virtual void StartScrolling(Point2F initialVelocity);

	virtual void ScrollTo(Point2F offset);
	virtual void ScrollBy(Point2F movement);
	virtual void ScrollToStart();
	virtual void ScrollToEnd();

	Point2F PageCount()const;

	Point2F Page()const;
	float PageX()const;
	float PageY()const;
	void ScrollByPage(Point2F page);
	void ScrollByPageX(float page);
	void ScrollByPageY(float page);

	void ScrollToPage(Point2F page);
	void ScrollToPageX(float page);
	void ScrollToPageY(float page);

	void UpdateWindow(const Size2F& sizeChanged, bool isApplyToLast = true);
	void UpdateContainer(const Size2F& sizeChanged, bool isApplyToLast = true);

	float HorizontalScrollBarOffset()const;
	float VerticalScrollBarOffset()const;
	Point2F ScrollBarOffset()const;


	float HorizontalScrollBarWidth()const;
	float VerticalScrollBarHeight()const;

	bool NeedHorizontalScrollBar()const;
	bool NeedVerticalScrollBar()const;

	virtual void Focus();
	virtual void Release();

	virtual bool UpdateModel(float dt);
protected:
	virtual void OnUpdate();
	virtual void OnRestrictScroll();
	virtual void OnScrollingEnd();
	virtual void OnScroll() {}

protected:
	ScrollDirection mDirection;

	ScrollState mState;

	Rect2F mContainer;
	Rect2F mCurrentWindow;
	Rect2F mPrevWindow;			//used to calculate movement 
	Point2F mInitialOffset;

	//limit bound
	RangeF mStaticLimitX;	//cache
	RangeF mStaticLimitY;	//cache

	Point2F mCurrentVelocity;	//cache
};

MEDUSA_END;
