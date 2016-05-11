// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IBehavior.h"
#include "Game/AI/Predicate/IPredicate.h"

MEDUSA_BEGIN;


class IPredicateBehavior :public IBehavior
{
	MEDUSA_DECLARE_RTTI;
public:
	IPredicateBehavior(const IPredicate* predicate = nullptr);
	~IPredicateBehavior(void);

	bool EvaluateBool(void* sender)const;
	int Evaluate(void* sender)const;

	const IPredicate* Predicate() const { return mPredicate; }
	void SetPredicate(const IPredicate* val);

	virtual bool LoadFromXmlNode(const pugi::xml_node& node)override;

protected:
	const IPredicate* mPredicate;
};

MEDUSA_END;
