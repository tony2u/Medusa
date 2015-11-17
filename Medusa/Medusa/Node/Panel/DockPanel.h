// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Panel/IPanel.h"

MEDUSA_BEGIN;


class DockPanel :public IPanel
{
	MEDUSA_DECLARE_RTTI;

public:
	DockPanel(StringRef name=StringRef::Empty);
	virtual ~DockPanel(void);
	virtual PanelType GetPanelType()const override{return PanelType::Dock;}

protected:
	virtual bool ArrangeChildren(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;
};



MEDUSA_END;
