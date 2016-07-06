// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IBehavior.h"
#include "Game/AI/Predicate/IPredicate.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;


class IPredicateBehavior :public IBehavior
{
	MEDUSA_RTTI(IPredicateBehavior,IBehavior);
public:
	IPredicateBehavior(const IPredicate* predicate = nullptr);
	~IPredicateBehavior(void);

	bool EvaluateBool(void* sender)const;
	int Evaluate(void* sender)const;

	const Share<IPredicate>& Predicate() const { return mPredicate; }
	void SetPredicate(const Share<IPredicate>& val) { mPredicate = val; }

	virtual bool LoadFromXmlNode(const pugi::xml_node& node)override;

protected:
	Share<IPredicate> mPredicate;
};

MEDUSA_END;
