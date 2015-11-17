// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInstantAction.h"
MEDUSA_BEGIN;

class ShowAction:public BaseInstantAction
{
public:
	ShowAction();
	virtual ~ShowAction(void);
public:
	virtual ShowAction* Clone()const override;
	virtual IAction* Reverse()const override;

	static ShowAction* Create();
protected:
	virtual bool OnAction() override;
};

MEDUSA_END;
