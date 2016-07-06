// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Game/AI/Behavior/IBehavior.h"

MEDUSA_BEGIN;


class IActBehavior:public IBehavior
{
	MEDUSA_RTTI(IActBehavior,IBehavior);
public:
	IActBehavior();
	virtual ~IActBehavior(void);
	virtual const IBehavior* Behave(IBrainBody& brainBody, void* sender)const override;

	virtual bool LoadFromXmlNode(const pugi::xml_node& node)override;

};

MEDUSA_END;
