// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IPredicateBehavior.h"

MEDUSA_BEGIN;

struct IfBehavior :public IPredicateBehavior
{
	MEDUSA_DECLARE_BEHAVIOR(IfBehavior,IPredicateBehavior);
public:
	virtual ~IfBehavior();
public:
	virtual const IBehavior* Behave(IBrainBody& brainBody, void* sender)const override;
	virtual const IBehavior* ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e)const override;
	virtual bool LoadFromXmlNode(const pugi::xml_node& node)override;

	void Add(const IBehavior* item);
	void AddElse(const IBehavior* item);
	virtual void Clear();

protected:
	List<const IBehavior*> mItems;
	List<const IBehavior*> mElseItems;

};

MEDUSA_END;
