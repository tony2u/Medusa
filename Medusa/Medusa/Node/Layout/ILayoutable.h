// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Point2.h"
#include "Geometry/Rect2.h"
#include "Geometry/Size2.h"
#include "Geometry/Thickness.h"
#include "Geometry/Padding4.h"
#include "Node/NodeDefines.h"
#include "Geometry/Scale2.h"
#include "Geometry/GeometryDefines.h"

MEDUSA_BEGIN;

class ILayoutable
{
public:
	ILayoutable();
	virtual ~ILayoutable(void);
public:
	virtual void UpdateLayout(const Size2F& availableSize=Size2F::Zero);
	virtual Rect2F ArrangeSelf(const Rect2F& limitRect=Rect2F::Zero,NodeLayoutArrangeFlags arrangeFlags=NodeLayoutArrangeFlags::None);
	virtual bool ArrangeChildren(const Rect2F& limitRect=Rect2F::Zero,NodeLayoutArrangeFlags arrangeFlags=NodeLayoutArrangeFlags::None);

	virtual bool ArrangeRecursively(const Rect2F& limitRect=Rect2F::Zero,NodeLayoutArrangeFlags arrangeFlags=NodeLayoutArrangeFlags::None);
protected:
	virtual void Measure(const Size2F& availableSize)=0;
	virtual void OnBeforeMeasure(const Size2F& availableSize)=0;
	virtual void OnAfterMeasure(const Size2F& availableSize)=0;

	virtual void OnLayoutChanged(const ILayoutable& sender,NodeLayoutChangedFlags changedFlag)=0;
	virtual bool IsSensitiveToChildLayoutChanged(const ILayoutable& sender,NodeLayoutChangedFlags changedFlag){return true;}

public:
	const Point2F& RelativePosition() const { return mRelativePosition; }
	void SetRelativePosition(const Point2F& val);

	DockPoint Dock() const { return mDockPoint; }
	void SetDock(DockPoint val);

	Stretch GetStretch() const { return mStretch; }
	void SetStretch(Stretch val);

	const Scale2F& StretchPercent() const { return mStretchPercent; }
	void SetStretchPercent(const Scale2F& val);

	SizeToContent GetSizeToContent() const { return mSizeToContent; }
	void SetSizeToContent(SizeToContent val) { mSizeToContent = val; }

	float StretchAspectRatio() const { return mStretchAspectRatio; }
	void SetStretchAspectRatio(float val) { mStretchAspectRatio = val; }

	const Padding4F& Padding() const { return mPadding; }
	void SetPadding(const Padding4F& val);

	const ThicknessF& Margin() const { return mMargin; }
	void SetMargin(const ThicknessF& val);
	MarginEdges MarginEdge() const { return mMarginEdge; }
	void SetMarginEdge(MarginEdges val);

	Direction GetDirection() const { return mDirection; }
	void SetDirection(Direction val);

	const Size2F& MeasuredSize() const { return mMeasuredSize; }
	void SetMeasuredSize(const Size2F& val) { mMeasuredSize = val; }

	bool IsLayoutEnabled() const { return mLayoutEnabled; }
	void EnableLayout(bool val);

	bool IsCollapsed() const { return mIsCollapsed; }
	void EnableCollapsed(bool val);
protected:
	void OnLayoutSizeChanged(const Size2F& newSize);
	void OnLayoutSizeChanged(const Size3F& newSize);


protected:
	Size2F mMinSize;
	Size2F mMaxSize;
	ThicknessF mMargin;	//not used now
	MarginEdges mMarginEdge=MarginEdges::None;
	
	Padding4F mPadding;	//not used now
	
	//adjust size
	Stretch mStretch= Stretch::None;
	SizeToContent mSizeToContent= SizeToContent::None;
	
	bool mIsStretchToSize=false;	//stretch to size instead of scale
	Scale2F mStretchPercent;	//stretch to parent size
	float mStretchAspectRatio=0.f;	//W/H
	
	//adjust position
	DockPoint mDockPoint= DockPoint::None;
	Point2F mRelativePosition;	//relative position of its parent,if dock point isn't none, this means the offset of dock point

	Direction mDirection=Direction::Horizontal;	//direction to arrange child items
	
	FlowDirection mFlowDirection= FlowDirection::LeftToRight;	//direction to arrange self's content, eg. label
	Size2F mMeasuredSize;	//cache

	bool mLayoutEnabled=true;
	bool mIsCollapsed=false;	//do not reserve space for it in layout.
	


};

MEDUSA_END;
