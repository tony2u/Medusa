// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;


enum class ScrollDirectionHorizontal
{
	None = 0,
	Left = 1,
	Right = 2,
	Free = Left | Right
};

enum class ScrollDirectionVertical
{
	None = 0,
	Bottom = 1,
	Top = 2,
	Free = Bottom | Top
};


struct ScrollDirection
{
	const static uint None = 0;
	const static uint HorizontalFromLeft = 2;	//2nd bit
	const static uint HorizontalFromRight = 4;	//3rd bit

	const static uint VerticalFromBottom = 8;	//4th bit
	const static uint VerticalFromTop = 16;		//5th bit
	const static uint FreeFromLeftBottom = HorizontalFromLeft | VerticalFromBottom;		//10
	const static uint FreeFromLeftTop = HorizontalFromLeft | VerticalFromTop;	//18
	const static uint FreeFromRightBottom = HorizontalFromRight | VerticalFromBottom;//12
	const static uint FreeFromRightTop = HorizontalFromRight | VerticalFromTop;	//20
	const static uint FreeFromCurrent = FreeFromLeftBottom | FreeFromRightTop;	//30

	const static uint HorizontalMask = HorizontalFromLeft | HorizontalFromRight;	//6
	const static uint VerticalMask = VerticalFromBottom | VerticalFromTop;	//24


	ScrollDirection(uint val = 0) :mValue(val) {}
	operator uint()const { return mValue; }
	ScrollDirection operator|(const ScrollDirection& val)const { return mValue | val.mValue; }
	ScrollDirection operator&(const ScrollDirection& val)const { return mValue & val.mValue; }
	ScrollDirection&  operator|=(const ScrollDirection& val) { mValue |= val.mValue; return *this; }
	ScrollDirection&  operator&=(const ScrollDirection& val) { mValue &= val.mValue; return *this; }





	MEDUSA_FORCE_INLINE bool IsHorizontal()const { return mValue == ScrollDirection::HorizontalFromLeft || mValue == ScrollDirection::HorizontalFromRight; }
	MEDUSA_FORCE_INLINE bool IsVertical() const { return mValue == ScrollDirection::VerticalFromBottom || mValue == ScrollDirection::VerticalFromTop; }

	MEDUSA_FORCE_INLINE bool HasHorizontal() const { return (mValue & HorizontalMask) != 0; }
	MEDUSA_FORCE_INLINE bool HasVertical() const { return (mValue & VerticalMask) != 0; }
	MEDUSA_FORCE_INLINE bool IsFree()const { return (mValue & HorizontalMask) != 0 && (mValue & VerticalMask) != 0; }
	MEDUSA_FORCE_INLINE bool IsFreeOrNone()const { return IsFree() || mValue == None; }


	MEDUSA_FORCE_INLINE bool HasLeft() const { return (mValue & HorizontalFromLeft) == HorizontalFromLeft; }
	MEDUSA_FORCE_INLINE bool HasRight() const { return (mValue & HorizontalFromRight) == HorizontalFromRight; }
	MEDUSA_FORCE_INLINE bool HasBottom() const { return (mValue & VerticalFromBottom) == VerticalFromBottom; }
	MEDUSA_FORCE_INLINE bool HasTop() const { return (mValue & VerticalFromTop) == VerticalFromTop; }

	ScrollDirectionHorizontal ToHorizontal()const { return (ScrollDirectionHorizontal)((mValue & HorizontalMask) >> 1); }
	ScrollDirectionVertical ToVertical()const { return (ScrollDirectionVertical)((mValue & VerticalMask) >> 3); }

private:
	uint mValue;
};


MEDUSA_END;
