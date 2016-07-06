// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Panel/IPanel.h"

MEDUSA_BEGIN;

//use default behavior
class RelativePanel :public IPanel
{
	MEDUSA_NODE(RelativePanel,IPanel);

public:
	using IPanel::IPanel;
	virtual ~RelativePanel(void);
	virtual PanelType GetPanelType()const override{return PanelType::Relative;}
protected:

};



MEDUSA_END;
