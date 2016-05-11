// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IPredicateBehavior.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

struct SwitchBehavior :public IPredicateBehavior
{
	MEDUSA_DECLARE_RTTI;
public:
	virtual ~SwitchBehavior();
public:
	virtual const IBehavior* Behave(IBrainBody& brainBody, void* sender)const override;
	virtual const IBehavior* ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e)const override;
	virtual bool LoadFromXmlNode(const pugi::xml_node& node)override;

protected:
	Dictionary<int, List<const IBehavior*>*> mItems;
	List<const IBehavior*> mDefaultItems;
};

MEDUSA_END;
