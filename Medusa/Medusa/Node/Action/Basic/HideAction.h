// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInstantAction.h"
MEDUSA_BEGIN;

class HideAction:public BaseInstantAction
{
public:
	HideAction();
	virtual ~HideAction(void);
public:

	virtual HideAction* Clone()const override;
	virtual IAction* Reverse()const override;

	static HideAction* Create();
protected:
	virtual bool OnAction() override;
};

MEDUSA_END;
