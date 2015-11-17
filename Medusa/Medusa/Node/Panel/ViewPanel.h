// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Panel/IPanel.h"

MEDUSA_BEGIN;


class ViewPanel :public IPanel
{
	MEDUSA_DECLARE_RTTI;

public:
	ViewPanel(StringRef name=StringRef::Empty);
	virtual ~ViewPanel(void);
	virtual PanelType GetPanelType()const override{return PanelType::View;}

	Stretch ChildStretch() const { return mChildStretch; }
	void SetChildStretch(Stretch val) { mChildStretch = val; }
protected:
	virtual bool ArrangeChildren(const Rect2F& limitRect=Rect2F::Zero,NodeLayoutArrangeFlags arrangeFlags=NodeLayoutArrangeFlags::None)override;
protected:
	Stretch mChildStretch;
	

};



MEDUSA_END;
