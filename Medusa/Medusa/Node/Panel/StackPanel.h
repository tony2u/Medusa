// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Panel/IPanel.h"

MEDUSA_BEGIN;


class StackPanel :public IPanel
{
	MEDUSA_NODE(StackPanel,IPanel);

public:

	StackPanel(StringRef name=StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~StackPanel(void);
	virtual PanelType GetPanelType()const override{return PanelType::Stack;}
protected:
	virtual bool ArrangeChildren(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;
protected:
	Size2F mItemFixedSize;	//fixed size for item size,item will be arranged in fixed size
};



MEDUSA_END;
