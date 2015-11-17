// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"

MEDUSA_BEGIN;


class IPanel :public INode
{
	MEDUSA_DECLARE_RTTI;
public:
	IPanel(StringRef name=StringRef::Empty);
	virtual ~IPanel(void);
public:
	virtual PanelType GetPanelType()const=0;
protected:
	virtual bool IsSensitiveToChildLayoutChanged(const ILayoutable& sender,NodeLayoutChangedFlags changedFlag) override {return true;}


};



MEDUSA_END;
