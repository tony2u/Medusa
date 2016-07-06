// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StateEventConnector.h"
#include "Game/AI/Predicate/IPredicate.h"
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;

StateEventConnector::StateEventConnector()
{
}

StateEventConnector::~StateEventConnector(void)
{
	
}

bool StateEventConnector::IsFit(IEventArg& e) const
{
	return e.ClassName() == mEventType;
}


MEDUSA_END;

