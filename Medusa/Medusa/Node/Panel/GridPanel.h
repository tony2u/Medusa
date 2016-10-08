// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Panel/IPanel.h"

MEDUSA_BEGIN;


class GridPanel :public IPanel
{
	MEDUSA_NODE(GridPanel,IPanel);

public:
	using IPanel::IPanel;
	virtual ~GridPanel(void);
	virtual PanelType GetPanelType()const override{return PanelType::Grid;}
protected:
	virtual bool ArrangeChildren(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;

};
MEDUSA_ENABLE_STATIC_CONSTRUCTOR(GridPanel);



MEDUSA_END;
