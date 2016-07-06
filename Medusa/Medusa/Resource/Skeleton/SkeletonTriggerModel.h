// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/HeapString.h"
#include "Core/Event/EventArg/TriggerEventArg.h"

MEDUSA_BEGIN;

class SkeletonTriggerModel
{
public:
	SkeletonTriggerModel(const StringRef& name);
	~SkeletonTriggerModel();
	StringRef Name() const { return mName; }

	const TriggerEventArg& EventArg() const { return mEventArg; }
	TriggerEventArg& MutableEventArg() { return mEventArg; }

	void SetEventArg(const TriggerEventArg& val) { mEventArg = val; }
protected:
	HeapString mName;
	TriggerEventArg mEventArg;
	
};

MEDUSA_END;
