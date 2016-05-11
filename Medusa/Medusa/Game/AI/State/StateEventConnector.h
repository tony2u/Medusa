// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IStateConnector.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class StateEventConnector:public IStateConnector
{
public:
	StateEventConnector();
	virtual ~StateEventConnector(void);
public:
	StringRef EventType() const { return mEventType; }
	void SetEventType(StringRef val) { mEventType = val; }

	bool IsFit(IEventArg& e)const;
protected:
	HeapString mEventType;
	
};

MEDUSA_END;
