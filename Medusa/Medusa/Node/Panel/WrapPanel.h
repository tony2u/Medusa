// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Panel/IPanel.h"

MEDUSA_BEGIN;

/*
like StackPanel, but WrapPanel will expand line if full
*/
class WrapPanel :public IPanel
{
	MEDUSA_NODE(WrapPanel,IPanel);

public:
	WrapPanel(StringRef name=StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~WrapPanel(void);
	virtual PanelType GetPanelType()const override{return PanelType::Wrap;}
	const Point2F& ItemOffset() const { return mItemOffset; }
	void SetItemOffset(const Point2F& val) { mItemOffset = val; }
protected:
	virtual bool ArrangeChildren(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;
protected:
	Size2F mItemFixedSize;	//fixed size for item size,item will be arranged in fixed size
	Point2F mItemOffset;
	
};



MEDUSA_END;
