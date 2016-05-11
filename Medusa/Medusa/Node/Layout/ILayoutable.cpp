// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ILayoutable.h"
#include "Geometry/Size3.h"

MEDUSA_BEGIN;


ILayoutable::ILayoutable( )
	:mMinSize(Size2F::Zero),
	mMaxSize(Size2F::Zero),
	mMargin(ThicknessF::Zero),
	mPadding(Padding4F::Zero),
	mStretchPercent(Scale2F::One),
	mRelativePosition(Point2F::Zero)
{

}

ILayoutable::~ILayoutable( void )
{
}

void ILayoutable::UpdateLayout(const Size2F& availableSize/*=Size2F::Zero*/)
{
	Measure(availableSize);
	ArrangeRecursively(Rect2F(Point2F::Zero,mMeasuredSize));
	
}

Rect2F ILayoutable::ArrangeSelf(const Rect2F& limitRect/*=Rect2F::Zero*/,NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return limitRect;
}

bool ILayoutable::ArrangeRecursively(const Rect2F& limitRect/*=Rect2F::Zero*/,NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

bool ILayoutable::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/,NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	return true;
}

void ILayoutable::EnableLayout(bool val)
{
	RETURN_IF_EQUAL(mLayoutEnabled,val);
	mLayoutEnabled = val;
}

void ILayoutable::SetRelativePosition(const Point2F& val)
{
	RETURN_IF_EQUAL(mRelativePosition, val);
	mRelativePosition = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::PositionChanged);

}

void ILayoutable::SetDock(DockPoint val)
{
	RETURN_IF_EQUAL(mDockPoint, val);

	mDockPoint = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::PositionChanged);

}

void ILayoutable::SetStretch(Stretch val)
{
	RETURN_IF_EQUAL(mStretch, val);

	mStretch = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::SizeChanged);

}

void ILayoutable::SetStretchPercent(const Scale2F& val)
{
	RETURN_IF_EQUAL(mStretchPercent, val);

	mStretchPercent = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::SizeChanged);

}


void ILayoutable::SetPadding(const Padding4F& val)
{
	RETURN_IF_EQUAL(mPadding, val);

	mPadding = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::ArrangeChanged);

}

void ILayoutable::SetMargin(const ThicknessF& val)
{
	RETURN_IF_EQUAL(mMargin, val);

	mMargin = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::ArrangeChanged);
}

void ILayoutable::SetMarginEdge(MarginEdges val)
{
	RETURN_IF_EQUAL(mMarginEdge, val);
	mMarginEdge = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::ArrangeChanged);
}

void ILayoutable::SetDirection(Direction val)
{
	RETURN_IF_EQUAL(mDirection, val);

	mDirection = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::ArrangeChanged);
}

void ILayoutable::EnableCollapsed(bool val)
{
	RETURN_IF_EQUAL(mIsCollapsed, val);
	mIsCollapsed = val;
	OnLayoutChanged(*this, NodeLayoutChangedFlags::CollapseChanged);

}

void ILayoutable::OnLayoutSizeChanged(const Size2F& newSize)
{
	if (Math::IsZero(mStretchAspectRatio) && !Math::IsZero(newSize.Height))
	{
		mStretchAspectRatio = newSize.Width / newSize.Height;
	}
}

void ILayoutable::OnLayoutSizeChanged(const Size3F& newSize)
{
	if (Math::IsZero(mStretchAspectRatio) && !Math::IsZero(newSize.Height))
	{
		mStretchAspectRatio = newSize.Width / newSize.Height;
	}
}


MEDUSA_END;
